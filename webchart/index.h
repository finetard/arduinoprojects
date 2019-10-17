const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
    <title>Line Chart</title>
    <script async="" src="//www.google-analytics.com/analytics.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/moment.js/2.13.0/moment.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.8.0/Chart.min.js"></script>
    <script src="utils.js"></script>
    <style>
        canvas {
            -moz-user-select: none;
            -webkit-user-select: none;
            -ms-user-select: none;
        }
    </style>
    <style type="text/css">
        /* Chart.js */
        @keyframes chartjs-render-animation {
            from {
                opacity: .99
            }

            to {
                opacity: 1
            }
        }

        .chartjs-render-monitor {
            animation: chartjs-render-animation 1ms
        }

        .chartjs-size-monitor,
        .chartjs-size-monitor-expand,
        .chartjs-size-monitor-shrink {
            position: absolute;
            direction: ltr;
            left: 0;
            top: 0;
            right: 0;
            bottom: 0;
            overflow: hidden;
            pointer-events: none;
            visibility: hidden;
            z-index: -1
        }

        .chartjs-size-monitor-expand>div {
            position: absolute;
            width: 1000000px;
            height: 1000000px;
            left: 0;
            top: 0
        }

        .chartjs-size-monitor-shrink>div {
            position: absolute;
            width: 200%;
            height: 200%;
            left: 0;
            top: 0
        }
    </style>
</head>

<body>
    <div style="width:75%;">
        <div class="chartjs-size-monitor">
            <div class="chartjs-size-monitor-expand">
                <div class=""></div>
            </div>
            <div class="chartjs-size-monitor-shrink">
                <div class=""></div>
            </div>
        </div>
        <canvas id="canvas" width="926" height="463" class="chartjs-render-monitor"
            style="display: block; width: 926px; height: 463px;"></canvas>
    </div>

    <script>
        var Socket;
        var values = [];
        var timeStamp = [];

        var color = Chart.helpers.color;
        var config = {
            type: 'line',
            data: {
                labels: timeStamp, //Bottom Labeling
                datasets: [{
                    label: "Voltage 1",
                    fill: false, //Try with true
                    backgroundColor: 'rgba( 243, 156, 18 , 1)', //Dot marker color
                    borderColor: 'rgba( 243, 156, 18 , 1)', //Graph Line Color
                    data: values,
                }],
            },
            options: {
                title: {
                    display: true,
                    text: "ADC Voltage"
                },
                maintainAspectRatio: false,
                elements: {
                    line: {
                        tension: 0.5 //Smoothening (Curved) of data lines
                    }
                },
                scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero: true
                        }
                    }]
                }
            }
        };

        window.onload = function () {
            var ctx = document.getElementById('canvas').getContext('2d');
            window.myLine = new Chart(ctx, config);
            start();
        };

        function start() {
            Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
            Socket.onmessage = function (evt) {
                var time = new Date().toLocaleTimeString();
                // document.getElementById("rxConsole").value += evt.data;
                config.data.datasets.forEach((dataset) => {
                    dataset.values.push(evt.data);
                })
                config.data.labels.timeStamp.push(time);
                window.myLine.update(); //Update Graphs
            }
        }
    </script>
</body>

</html>

)=====";
