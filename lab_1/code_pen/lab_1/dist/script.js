let lightsOn = false;
let autoMode = false;
const lights = document.querySelectorAll('.light');
const statusText = document.getElementById('status');
const movementSlider = document.getElementById('movement-slider');

document.getElementById('toggle-light').addEventListener('click', () => {
    if (!autoMode) {
        lightsOn = !lightsOn;
        lights.forEach(light => light.classList.toggle('on', lightsOn));
    }
});

document.getElementById('toggle-auto').addEventListener('click', () => {
    autoMode = !autoMode;
    lightsOn = false;
    lights.forEach(light => light.classList.remove('on'));
    statusText.textContent = autoMode ? 'Auto Mode' : 'Manual Mode';
});

movementSlider.addEventListener('input', () => {
    if (autoMode && movementSlider.value > 30) {
        simulateMovement();
    }
});

function simulateMovement() {
    lights.forEach(light => light.classList.add('on'));
    setTimeout(() => {
        lights.forEach(light => light.classList.remove('on'));
    }, 5000);
}