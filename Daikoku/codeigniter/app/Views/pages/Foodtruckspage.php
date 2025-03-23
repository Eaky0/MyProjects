<?php

$CountryFilter = $data[0];
$KitchenFilter = $data[1];
$VehicleFilter = $data[2];
$PriceRangeFilter = $data[3];

?>




<div id="SearchSection" class="container">
  <div id="SectionText" class="row">
    <div class="col text-center">
      <h1 class="display-1">Food Trucks</h1>
    </div>
  </div>
    <div class="row">
      <div class="col-lg-11 col-md-12 d-flex justify-content-center">
        <input oninput="fetchSearch()" id="SearchBar" type="text" class="form-control form-control-lg SearchFunctions" placeholder="Find your Foodtruck!">
      </div>
      <div class="col-lg-1 col-md-12 d-flex justify-content-center">
        <button class="btn btn-primary rounded-pill btn-lg bg-black border-black SearchFunctions" type="button" data-bs-toggle="offcanvas" data-bs-target="#offcanvasExample" aria-controls="offcanvasExample">Filter</button>
      </div>
    </div>
    <div class="offcanvas offcanvas-start" data-bs-backdrop="static" tabindex="-1" id="offcanvasExample" aria-labelledby="offcanvasExampleLabel">
          <div class="offcanvas-header">
            <h5 class="offcanvas-title" id="offcanvasExampleLabel">Filter</h5>
            <button type="button" class="btn-close" data-bs-dismiss="offcanvas" aria-label="Close"></button>
          </div>
                  <div class="offcanvas-body">
                    <div class="accordion accordion-flush" id="accordionPanel">
                    <form id="filterform">
                    <input type="hidden" name="<?= csrf_token() ?>" value="<?= csrf_hash() ?>"/>
                      <div class="accordion-item">
                        <h2 class="accordion-header" id="panel-headingCountry">
                          <button class="accordion-button collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#panel-collapseCountry" aria-expanded="true" aria-controls="panel-collapseCountry">
                            Country
                          </button>
                        </h2>
                        <div id="panel-collapseCountry" class="accordion-collapse collapse" aria-labelledby="panel-headingCountry">
                          <div class="accordion-body">
                            <?php foreach($CountryFilter as $index => $Country): ?>
                              <div class="list-group-item">
                                  <input class="form-check-input" type="checkbox" id=<?= $Country['Country']?>>
                                  <label class="form-check-label" ><?= $Country['Country']?></label>
                              </div>
                            <?php endforeach ?>
                            </div>
                          </div>
                        </div>
                        <div class="accordion-item">
                          <h2 class="accordion-header" id="panel-headingKitchen">
                            <button class="accordion-button collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#panel-collapseKitchen" aria-expanded="true" aria-controls="panel-collapseKitchen">
                              Kitchen
                            </button>
                          </h2>
                          <div id="panel-collapseKitchen" class="accordion-collapse collapse " aria-labelledby="panel-headingKitchen">
                            <div class="accordion-body">
                            <?php foreach($KitchenFilter as $index => $Kitchen): ?>
                              <div class="list-group-item">
                                  <input class="form-check-input" type="checkbox"  id=<?= $Kitchen['Kitchen']?>>
                                  <label class="form-check-label" ><?= $Kitchen['Kitchen']?></label>
                              </div>
                            <?php endforeach ?>
                              </div>
                            </div>
                          </div>
                          <div class="accordion-item">
                            <h2 class="accordion-header" id="panel-headingVehicle">
                              <button class="accordion-button collapsed" type="button" data-bs-toggle="collapse" data-bs-target="#panel-collapseVehicle" aria-expanded="true" aria-controls="panel-collapseVehicle">
                                Vehicle
                              </button>
                            </h2>
                            <div id="panel-collapseVehicle" class="accordion-collapse collapse" aria-labelledby="panel-headingVehicle">
                              <div class="accordion-body">
                              <?php foreach($VehicleFilter as $index => $Vehicle): ?>
                              <div class="list-group-item">
                                  <input class="form-check-input" type="checkbox"  id=<?= $Vehicle['Vehicle']?>>
                                  <label class="form-check-label" ><?= $Vehicle['Vehicle']?></label>
                              </div>
                            <?php endforeach ?>
                                </div>
                              </div>
                            </div>
                        </div>
                        <br>
                        <label for="Price-Range">Price Range: <span id="Range-Value" class="h5">€ <?= $PriceRangeFilter['MaxPrice']?>.00</span></label>
                        <input type="range" min="<?= $PriceRangeFilter['MinPrice']?>" max="<?= $PriceRangeFilter['MaxPrice']?>" value="<?= $PriceRangeFilter['MaxPrice']?>" step="1" id="Price-Range" class="form-range" > 
                    </div>
                    <button onclick="FetchFilter()" id="Savebutton" type="button" class="btn bg-black" data-bs-dismiss="offcanvas">Save</button>
                    </form>
                  </div>
                </div>
              </div>
          </div>
      


      <div class="container">
      <div id="FoodTruckSection" class="row">
        <!--<div class="col-lg-3 col-md-6 col-sm-6 d-flex justify-content-center">
          <div class="card shadow FoodTruckCard">
            <div class="card-body">
              <form action="base_url("FoodTruckinfopage")" method="post">
              <input type="hidden" name="FoodTruckName" value=$FoodTruck['Name']>
              <img src="FoodtruckStaticIcon.png" class="w-100" alt="Food truck Photo">
              <h5 class="card-title">FoodFyte</h5>
              <button type="submit" class="btn btn-primary text-black bg-white border-black">Check it out!</button>
              </form>
            </div>
          </div>  
        </div> -->

      </div>
    </div>
    
<script>
var headers = new Headers();
headers.append("Accept", "application/json");
headers.append('X-Requested-With', 'XMLHttpRequest');
headers.append('X-CSRF-TOKEN', '<?= csrf_hash() ?>');
</script>
