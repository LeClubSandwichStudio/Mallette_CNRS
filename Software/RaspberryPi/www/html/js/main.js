var acq;

$(document).ready(() => {
  var log_name;
  $.get("logs/lastlog.txt", (data) => {
    let dl = document.getElementById('dl_btn');
    dl.href = `logs/${data}`;
  });


});


function Stop() {
  alert("Stopping");
  clearInterval(acq);

  $.ajax({
    type: "POST",
    url: "command.php",
    data: {
      "Stop": true
    },
    success: started = false,
  });
}

function Start() {
  let t = $("#time_input").val();

  // Creation fichier pour script Python
  $.ajax({
    type: "POST",
    url: "command.php",
    data: {
      "Start": true,
      "Time": t,
    },
    success: getData(t),
  });
}

function getData(acqTime) {
  alert("Acquiring data");
  let sums = [0, 0, 0, 0] // Sums of data
  let nb = 1 // Average divider
  let saveData = [];
  let begin = Date.now();

  acq = setInterval(() => {
    // Verifie si le temps d'acquisition est depasse
    if (Date.now() - begin > acqTime * 1000)
      clearInterval(acq);

    $.get("data/data.txt", (data) => {
      data = data.substring(0, data.indexOf(' '));
      data = JSON.parse(data);
      sensors = data.sensors;

      let table = document.getElementById("table_data");

      let row = table.insertRow(); // Create a row in the table

      let d = [sensors.temperature, sensors.ph, sensors.ec, sensors.turbidity];
      // Add data to sums array
      for (let i = 0; i < sums.length; i++)
        sums[i] += d[i];

      console.log(sums);


      // For each key in JSON object, append data in the table
      for (key in sensors) {
        let cell = row.insertCell(); // Create a cell in the row

        if (key == "time") {
          let currentDate = new Date();
          let time = currentDate.getHours() + ":" + currentDate.getMinutes() + ":" + currentDate.getSeconds();
          let text = document.createTextNode(time);
          cell.appendChild(text);
        } else {
          let text = document.createTextNode(sensors[key]);
          cell.appendChild(text);
        }
      }

      // Set texts
      $('#div_refresh_temperature').text(d[0]);
      $('#div_refresh_ph').text(d[1]);
      $('#div_refresh_ec').text(d[2]);;
      $('#div_refresh_turb').text(d[3]);

      // Set averages
      let avg = sums[0] / nb;
      $('#temp_avg').text(avg.toFixed(2));
      avg = sums[1] / nb;
      $('#ph_avg').text(avg.toFixed(2));
      avg = sums[2] / nb;
      $('#ec_avg').text(avg.toFixed(2));
      avg = sums[3] / nb;
      $('#turb_avg').text(avg.toFixed(2));

      nb++; // Increase divider
    });
  }, 1000);
}
