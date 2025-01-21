let time = document.getElementById("Time");
let submit = document.getElementById("Submit");

let t = new Date();
let currentDate = t.toISOString().slice(0,19);

console.log(currentDate);

time.value = currentDate;

// script must be loaded to allow submitting
submit.disabled = false;