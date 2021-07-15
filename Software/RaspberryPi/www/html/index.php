<?php
    $strList = explode(" ", file_get_contents("data/commandeWeb.txt"));
    $id = $strList[0];

    if(isset($_POST["start_btn"])){
        $id = $id + 1;
        file_put_contents("data/commandeWeb.txt", $id.",start,".$_POST["time"]);
    }
    else if(isset($_POST["stop_btn"])){
        $id = $id + 1;
        file_put_contents("data/commandeWeb.txt", $id.",stop");
    }
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Water Briefcase Analyzer</title>

    <!-- Custom fonts for this template-->
    <link href="vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css">
    <link
        href="https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i"
        rel="stylesheet">

    <!-- Custom styles for this template-->
    <link href="css/sb-admin-2.min.css" rel="stylesheet">
    <link href="css/style.css" rel="stylesheet">
    <script src="libs/jquery-3.2.1.min.js"></script>
    <script src="libs/jquery-3.2.1.min.js"></script>
    <script src="js/main.js"></script>

</head>


<body id="page-top">

    <!-- Page Wrapper -->
    <div id="wrapper">

        <!-- Sidebar -->
        <ul class="navbar-nav bg-gradient-primary sidebar sidebar-dark accordion" id="accordionSidebar">

            <!-- Sidebar - Brand -->
            <a class="sidebar-brand d-flex align-items-center justify-content-center" href="index.php">
                <div class="sidebar-brand-icon">
                    <i class="fas fa-tint"></i>
                </div>
                <div class="sidebar-brand-text mx-3">Water Case</div>
            </a>

            <!-- Divider -->
            <hr class="sidebar-divider">

            <!-- Nav Item - Dashboard -->
            <!-- Heading -->
            <div class="sidebar-heading">
                Interface
            </div>
            <li class="nav-item active">
                <a class="nav-link" href="index.php">
                    <i class="fas fa-fw fa-tachometer-alt"></i>
                    <span>Dashboard</span></a>
            </li>

            <!-- Divider -->
            <hr class="sidebar-divider">
            <div class="sidebar-heading">
                Calibration
            </div>
            <li class="nav-item active">
                <a class="nav-link" href="ph_clb.php">
                    <i class="fas fa-fw fa-flask"></i>
                    <span>PH</span></a>
            </li>
            <li class="nav-item active">
                <a class="nav-link" href="ec_clb.php">
                    <i class="fas fa-fw fa-bolt"></i>
                    <span>Electroconductivity</span></a>
            </li>
            <li class="nav-item active">
                <a class="nav-link" href="turb_clb.php">
                    <i class="fas fa-fw fa-braille"></i>
                    <span>Turbidity</span></a>
            </li>

            <!-- Divider -->
            <hr class="sidebar-divider">

        </ul>
        <!-- End of Sidebar -->

        <!-- Content Wrapper -->
        <div id="content-wrapper" class="d-flex flex-column">

            <!-- Main Content -->
            <div id="content">

                <!-- Topbar -->
                <!-- End of Topbar -->

                <!-- Begin Page Content -->
                <div class="container-fluid">

                    <!-- Page Heading -->
                    <div class="d-sm-flex align-items-center justify-content-between mb-4" style="margin-top: 24px;">
                        <h1 class="h3 mb-0 text-gray-800">Dashboard</h1>
                    </div>

                    
                    <form name="form" method="post" action="">
                        <!-- Time input -->
                        <div>
                            <label for="time_input">Temps (s) :</label>
                            <input id="time_input" type="number" list="time_list" name="time" value="1" min="0" max="1000" />
                            <datalist id="time_list">
                                <option>1</option>
                                <option>3</option>
                                <option>5</option>
                                <option>10</option>
                            </datalist>
                        </div>
                        <!-- End of Time input -->
                        <br>
                        <!-- Top buttons -->
                        <div class="d-flex align-items-starts">
                            <!-- Start -->
                            <div class="p-2">
                                    <!--<input type="hidden" name="start_btn" value="a"/>-->
                                    <input type="submit" name="start_btn" value="Start">            
                            </div>
			</form>
                            <div class="p-2"> </div>

                            <!-- Stop -->
                            <div class="p-2">
                            	<input type="button" onclick="stop();" target="_blank" name="stop_btn" value="Stop"/>
                            </div>
                        </div>
                        <!-- End of Top buttons -->
                    

                    <!-- Save -->
                    <div class="p-2" style="align-self: center">
                        <a id="dl_btn" download target="_blank" class="btn btn-primary btn-icon-split">
                            <span class="icon text-white-50">
                                <i class="fas fa-save"></i>
                            </span>
                            <span class="text">Save</span>
                        </a>
                    </div>
                    <!-- End of Save -->
                   

                    <div class="row no-gutters align-items-center">
                        <div class="col-auto">
                            <div id="div_refresh_hour">°C</div>
                        </div>
                    </div>

                    <br>
                    <!-- Content Row -->
                    <div class="row">

                        <!-- Temperature Card -->
                        <div class="col-xl-3 col-md-6 mb-4">
                            <div class="card border-left-primary shadow h-100 py-2">
                                <div class="card-body">
                                    <div class="row no-gutters align-items-center flex-row-reverse">
                                        <a href="ec_clb.php" class="btn btn-info btn-circle btn-sm" style="visibility:hidden">
                                            <i class="fas fa-info-circle"></i>
                                        </a>
                                    </div>
                                    <div class="p-2"></div>
                                    <div class="row no-gutters align-items-center">
                                        <div class="col mr-2">
                                            <div class="row no-gutters align-items-center">
                                                <div class="text-xs font-weight-bold text-primary text-uppercase mb-1">
                                                    Temperature
                                                </div>
                                            </div>

                                            <div class="row no-gutters align-items-center">
                                                <div class="col-auto">
                                                    <div id="div_refresh_temperature"
                                                        class="h5 mb-0 mr-3 font-weight-bold text-gray-800"></div>
                                                </div>
                                                <div class="col-auto">
                                                    <div class="h5 mb-0 mr-3 font-weight-bold text-gray-800">°C</div>
                                                </div>

                                                <div class="col">
                                                    <div id="div_refresh_temperature_pgb"
                                                        class="progress progress-sm mr-2">

                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                        <div class="col-auto">
                                            <i class="fas fa-temperature-low fa-2x text-gray-300"></i>
                                        </div>
                                    </div>
                                    <br>
                                    <div class="row no-gutters align-items-center">
                                        <div class="col mr-2">
                                            <div class="text-xs font-weight-bold text-primary text-uppercase">
                                                AVERAGE :
                                            </div>
                                            <div id="temp_avg" class="text-xs font-weight-bold text-primary text-uppercase">
                                                0
                                            </div>
                                        </div>

                                    </div>

                                </div>
                            </div>
                        </div>

                        <!-- Ph Card -->
                        <div class="col-xl-3 col-md-6 mb-4">
                            <div class="card border-left-success shadow h-100 py-2">
                                <div class="card-body">
                                    <div class="row no-gutters align-items-center flex-row-reverse">
                                        <a href="ec_clb.php" class="btn btn-info btn-circle btn-sm">
                                            <i class="fas fa-info-circle"></i>
                                        </a>
                                    </div>
                                    <div class="p-2"></div>
                                    <div class="row no-gutters align-items-center">
                                        <div class="col mr-2">
                                            <div class="text-xs font-weight-bold text-success text-uppercase mb-1">PH
                                            </div>
                                            <div class="row no-gutters align-items-center">
                                                <div class="col-auto">
                                                    <div id="unit_ec"
                                                        class="h5 mb-0 mr-3 font-weight-bold text-gray-800">PH </div>

                                                </div>
                                                <div class="col-auto">
                                                    <div id="div_refresh_ph"
                                                        class="h5 mb-0 mr-3 font-weight-bold text-gray-800"></div>
                                                </div>
                                                <div class="col">
                                                    <div id="div_refresh_ph_pgb" class="progress progress-sm mr-2">
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                        <div class="col-auto">
                                            <i class="fas fa-flask fa-2x text-gray-300"></i>
                                        </div>
                                    </div>
                                    <br>
                                    <div class="row no-gutters align-items-center">
                                        <div class="col mr-2">
                                            <div class="text-xs font-weight-bold text-success text-uppercase">
                                                AVERAGE :
                                            </div>
                                            <div id="ph_avg" class="text-xs font-weight-bold text-success text-uppercase">
                                                0
                                            </div>
                                            <div class="row no-gutters align-items-center">
                                                <div class="col-auto">
                                                    <div id="div_refresh_ph"
                                                        class="h5 mb-0 mr-3 font-weight-bold text-gray-800"></div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>

                        <!-- Electro Conductivity Card -->
                        <div class="col-xl-3 col-md-6 mb-4">
                            <div class="card border-left-warning shadow h-100 py-2">
                                <div class="card-body">
                                    <div class="row no-gutters align-items-center flex-row-reverse">
                                        <a href="ec_clb.php" class="btn btn-info btn-circle btn-sm">
                                            <i class="fas fa-info-circle"></i>
                                        </a>
                                    </div>
                                    <div class="p-2"></div>
                                    <div class="row no-gutters align-items-center">
                                        <div class="col mr-2">
                                            <div class="text-xs font-weight-bold text-warning text-uppercase mb-1">
                                                Electro-conductivity
                                            </div>
                                            <div class="row no-gutters align-items-center">
                                                <div class="col-auto">
                                                    <div id="div_refresh_ec"
                                                        class="h5 mb-0 mr-3 font-weight-bold text-gray-800"></div>
                                                </div>
                                                <div class="col-auto">
                                                    <div id="unit_ec"
                                                        class="h5 mb-0 mr-3 font-weight-bold text-gray-800">µS/cm</div>
                                                </div>
                                                <div class="col">
                                                    <div id="div_refresh_ec_pgb" class="progress progress-sm mr-2">
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                        <div class="col-auto">
                                            <i class="fas fa-bolt fa-2x text-gray-300"></i>
                                        </div>
                                    </div>
                                    <br>
                                    <div class="row no-gutters align-items-center">
                                        <div class="col mr-2">
                                            <div class="text-xs font-weight-bold text-warning text-uppercase">
                                                AVERAGE :
                                            </div>
                                            <div id="ec_avg" class="text-xs font-weight-bold text-warning text-uppercase">
                                                0
                                            </div>
                                            <div class="row no-gutters align-items-center">
                                                <div class="col-auto">
                                                    <div id="div_refresh_temperature"
                                                        class="h5 mb-0 mr-3 font-weight-bold text-gray-800"></div>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>

                        <!-- Turbidity Card -->
                        <div class="col-xl-3 col-md-6 mb-4">
                            <div class="card border-left-info shadow h-100 py-2">
                                <div class="card-body">
                                    <div class="row no-gutters align-items-center flex-row-reverse">
                                        <a href="turb_clb.php" class="btn btn-info btn-circle btn-sm">
                                            <i class="fas fa-info-circle"></i>
                                        </a>
                                    </div>
                                    <div class="p-2"></div>
                                    <div class="row no-gutters align-items-center">
                                        <div class="col mr-2">
                                            <div class="text-xs font-weight-bold text-info text-uppercase mb-1">
                                                TURBIDITY
                                            </div>
                                            <div class="row no-gutters align-items-center">
                                                <div class="col-auto">
                                                    <div id="div_refresh_turb"
                                                        class="h5 mb-0 mr-3 font-weight-bold text-gray-800"></div>
                                                </div>
                                                <div class="col-auto">
                                                    <div id="unit_ec"
                                                        class="h5 mb-0 mr-3 font-weight-bold text-gray-800">LTU</div>
                                                </div>
                                                <div class="col">
                                                    <div id="div_refresh_turb_pgb" class="progress progress-sm mr-2">
                                                    </div>
                                                </div>
                                            </div>
                                        </div>
                                        <div class="col-auto">
                                            <i class="fas fa-braille fa-2x text-gray-300"></i>
                                        </div>
                                    </div>
                                    <br>
                                    <div class="row no-gutters align-items-center">
                                        <div class="col mr-2">
                                            <div class="text-xs font-weight-bold text-info text-uppercase">
                                                AVERAGE :
                                            </div>
                                            <div id="turb_avg" class="text-xs font-weight-bold text-info text-uppercase">
                                                0
                                            </div>
                                            <div class="row no-gutters align-items-center">
                                                <div class="col-auto">
                                                    <div id="div_refresh_temperature"
                                                        class="h5 mb-0 mr-3 font-weight-bold text-gray-800"></div>
                                                </div>
                                            </div>
                                        </div>

                                    </div>
                                </div>
                            </div>
                        </div>
                        
                         <table>
                            <thead>
                                <th>Temperature</th>
                                <th>Ph</th>
                                <th>Electro Conductivity</th>
                                <th>Turbidity</th>
				<th>Time</th>
                            </thead>
                            <tbody id="table_data">
                            </tbody>
                        </table>
                        
                        <!-- Content Row -->
                        <div class="row">
                        
                       


                            <!-- Area Chart -->



                            <!-- Area Chart -->


                        </div>


                    </div>
                    <!-- /.container-fluid -->
                    <div style="width: 100%;">
                        <table id="valTable" style="display: none">
                            <thead>
                                <th>Temperature</th>
                                <th>Ph</th>
                                <th>Electro-Conductivity</th>
                                <th>Turbidity</th>
                            </thead>
                            <tbody>
                            </tbody>
                        </table>
                    </div>

                </div>
                <!-- End of Main Content -->

                <!-- Footer -->
                <footer class="sticky-footer bg-white">
                    <div class="container my-auto">
                        <div class="copyright text-center my-auto">
                            <span>Le Club Sandwich Studio 2021</span>
                        </div>
                    </div>
                </footer>
                <!-- End of Footer -->

            </div>
            <!-- End of Content Wrapper -->

        </div>
        <!-- End of Page Wrapper -->

        <!-- Scroll to Top Button-->
        <a class="scroll-to-top rounded" href="#page-top">
            <i class="fas fa-angle-up"></i>
        </a>

        <!-- Logout Modal-->
        <div class="modal fade" id="logoutModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel"
            aria-hidden="true">
            <div class="modal-dialog" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title" id="exampleModalLabel">Ready to Leave?</h5>
                        <button class="close" type="button" data-dismiss="modal" aria-label="Close">
                            <span aria-hidden="true">×</span>
                        </button>
                    </div>
                    <div class="modal-body">Select "Logout" below if you are ready to end your current session.</div>
                    <div class="modal-footer">
                        <button class="btn btn-secondary" type="button" data-dismiss="modal">Cancel</button>
                        <a class="btn btn-primary" href="login.html">Logout</a>
                    </div>
                </div>
            </div>
        </div>

        <!-- Bootstrap core JavaScript-->
        <script src="vendor/jquery/jquery.min.js"></script>
        <script src="vendor/bootstrap/js/bootstrap.bundle.min.js"></script>

        <!-- Core plugin JavaScript-->
        <script src="vendor/jquery-easing/jquery.easing.min.js"></script>

        <!-- Custom scripts for all pages-->
        <script src="libs/sb-admin-2.min.js"></script>

        <!-- Page level plugins -->
        <script src="vendor/chart.js/Chart.min.js"></script>

        <!-- Page level custom scripts -->
        <script src="libs/demo/tempChart.js"></script>
        <script src="libs/demo/phChart.js"></script>
        <script src="libs/demo/ecChart.js"></script>
        <script src="libs/demo/turbChart.js"></script>
        <script src="libs/demo/chart-pie-demo.js"></script>

</body>

</html>
