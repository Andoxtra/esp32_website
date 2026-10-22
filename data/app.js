"use strict";

// --- API layer: the only place that talks to the ESP32 -------------------
const api = {
  async listPins() {
    return request("/api/pins", "GET");
  },
  async togglePin(id) {
    return request(`/api/pins/toggle?id=${encodeURIComponent(id)}`, "POST");
  },
};

async function request(url, method) {
  const response = await fetch(url, { method });
  if (!response.ok) throw new Error(`Request failed (${response.status})`);
  return response.json();
}

// --- View layer: DOM rendering only --------------------------------------
const view = {
  list: document.getElementById("pin-list"),
  status: document.getElementById("status"),

  showError(message) {
    this.status.textContent = message;
  },

  render(pins, onToggle) {
    this.status.textContent = "";
    this.list.replaceChildren(...pins.map((pin) => this.createCard(pin, onToggle)));
  },

  createCard(pin, onToggle) {
    const item = document.createElement("li");
    item.className = "pin-card";

    const info = document.createElement("div");
    info.innerHTML = '<div class="pin-name"></div><div class="pin-gpio"></div>';
    info.querySelector(".pin-name").textContent = pin.label;
    info.querySelector(".pin-gpio").textContent = `GPIO ${pin.gpio}`;

    const button = document.createElement("button");
    button.className = "pin-button" + (pin.high ? " high" : "");
    button.textContent = pin.high ? "HIGH" : "LOW";
    button.addEventListener("click", () => {
      button.disabled = true;
      onToggle(pin.id);
    });

    item.append(info, button);
    return item;
  },
};

// --- Controller: connects API and view -----------------------------------
async function refresh(action) {
  try {
    const pins = await action();
    view.render(pins, (id) => refresh(() => api.togglePin(id)));
  } catch (error) {
    view.showError(error.message);
  }
}

refresh(() => api.listPins());
