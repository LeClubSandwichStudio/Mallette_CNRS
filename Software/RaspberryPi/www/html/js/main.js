let sums = [0,0,0,0] // Sums of data
let nb = 0 // Average divider
let started = false;
let saveData = [];

var today = new Date();
var dd = String(today.getDate()).padStart(2, '0');
var mm = String(today.getMonth() + 1).padStart(2, '0'); //January is 0!
var yyyy = today.getFullYear();
var log_name = `logs/Logs-${dd}-${mm}-${yyyy}.txt`

function stop(){
  $.ajax({
      type: "POST",
      url: "index.php",
      data: {
           "stop_btn" : "stop"
      },
      success: alert("Data acquired"),
    }); 
}

$(document).ready(function(){
  var dl = document.getElementById("dl_btn");
  dl.href = log_name;
  getData = setInterval(function(){
    // Get data from file
    $.get("data.php", function(msg){
      msg = JSON.parse(msg);
      
      data = msg[0];
      input = msg[1];
      sep_index = [];
      
      for( let i = 0 ; i < input.length ; i++){
            if( input[i] == ','){
              sep_index.push(i)
            }
      }
      
      cmd = input.substring(sep_index[0]+1, sep_index[1]);
      
      if(cmd == "stop"){
          started = false;
          sums = [0,0,0,0] // Sums of data
          nb = 0 // Average divider
      }
      
      if(cmd == "start"){
            let table = document.getElementById("table_data");
            interval = input.substring(sep_index[1]+1, input.length);
            interval = parseInt(interval)*1000;
            
            if( !started ){
              started = true;
              t_start = Date.now();
            }
            
            
            data = data.substring(0, data.indexOf('\r'));
            
            if(data[0] == '{'){
              let arr = $.parseJSON(data); // Data array
              
              let row = table.insertRow();
              
              let sensors = arr.sensors;
              let d = [sensors.temperature, sensors.ph, sensors.ec, sensors.turbidity];
              
              saveData.push(sensors);
              
              for (key in sensors) {
                let cell = row.insertCell();
                if( key == "time" ){
                  let unix_timestamp = sensors[key]
                  var date = new Date(unix_timestamp * 1000);
                  var hours = date.getHours();
                  var minutes = "0" + date.getMinutes();
                  var seconds = "0" + date.getSeconds();
                  var formattedTime = hours + ':' + minutes.substr(-2) + ':' + seconds.substr(-2);
                  let text = document.createTextNode(formattedTime);
                  cell.appendChild(text);
                } else {
                  let text = document.createTextNode(sensors[key]);
                  cell.appendChild(text);
                }
              }

              // Add data to sums array
              for (let i = 0; i < sums.length; i++)
                sums[i] += d[i];

              nb++; // Increase divider

              // Set texts
              $('#div_refresh_temperature').text(d[0]);
              $('#div_refresh_ph').text(d[1]);
              $('#div_refresh_ec').text(d[2]);
              $('#div_refresh_turb').text(d[3]);

              // Set averages
              let avg = sums[0]/nb;
              $('#temp_avg').text(avg.toFixed(2));
              avg = sums[1]/nb;
              $('#ph_avg').text(avg.toFixed(2));
              avg = sums[2]/nb;
              $('#ec_avg').text(avg.toFixed(2));
              avg = sums[3]/nb;
              $('#turb_avg').text(avg.toFixed(2));

              // Set Progress bars
              //$('#div_refresh_temperature_pgb').text(d[0]);
              //$('#div_refresh_ph_pgb').text(d[1]*7);
              //$('#div_refresh_ec_pgb').text(d[2]*1000);
              //$('#div_refresh_turb_pgb').text(d[3]/30);
              
              if( Date.now() - t_start > interval){
                $.ajax({
                    type: "POST",
                    url: "index.php",
                    data: {
                         "stop_btn" : "stop"
                    },
                    success: alert("Data acquired"),
                  });
                clearInterval(getData);
              }
          }
      }
      
    });

    // $('#div_refresh_hour').load("data_hour.php");
  },200);
});
