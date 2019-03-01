const weather = document.querySelector(".js-weather");
const API_KEY = "2f54ae9c0a56d5f57b5f55e11fce7594"
const COORDS = "coords";

function getWeather(lat, lng) {
  fetch(`https://api.openweathermap.org/data/2.5/weather?lat=${lat}&lon=${lng}&appid=${API_KEY}&units=metric`)
  .then(function(response){
    return response.json();
  })
  .then(function(json) {
    const temperature = json.main.temp;
    const place = json.sys.country;
    weather.innerText = `${temperature}°C at ${place}`;
  });
}

function saveCoords(coordsObj) {
  localStorage.setItem(COORDS, JSON.stringify(coordsObj));
}

function handleGeoSuccess(position) {
  const latitude = position.coords.latitude;
  const longitude = position.coords.longitude;
  const coordsObj = {
    latitude, 
    longitude
  };

  saveCoords(coordsObj);
  getWeather(latitude, longitude);
}

function handleGeoError() {
  console.log('Cant access geo location. ');
}

function askForCoords() {
  navigator.geolocation.getCurrentPosition(handleGeoSuccess, handleGeoError);
}

function loadCoords() {
  const loadedCoords = localStorage.getItem(COORDS);

  if (loadedCoords === null) {
    askForCoords();
  } else {
    const parsedCoords = JSON.parse(loadedCoords);
    getWeather(parsedCoords.latitude, parsedCoords.longitude);
  }
}

function init() {
  loadCoords();
}

init();
