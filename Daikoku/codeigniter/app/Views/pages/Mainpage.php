<div class="container WelcomeTab">
    <div class="row justify-content-center align-items-center " style="height: 300px;">
      <div class="col-10">
        <h1 class="display-1">Welcome!</h1>
      </div>
      <div class="col-10">
        <p style="font-family: Impact; font-style: italic;">We are Daikoku, a foodtruck hiring company, operating throughout all of Europe! <br>
          You wouldn't want to miss out on all the food trucks we've got available for you.</p>
      </div>
    </div>

<?php if (session('LoggedIn') == true && session('UserType') == 'C'): ?>
    </div>


<div id="FoodTruckhl" class="container">
    <div class="row align-items-center " style="height:150px">
      <div class="col text-center">
        <h1 class="text-white">Our 
          <?php 
              if (count($foodtrucks) < 8){
                  echo (count($foodtrucks));
              }
              else{
                  echo 8;
              }?> best-hired Food Trucks!</h1>
      </div>
    </div>



    <div id="Top8Section" class="row">

    <?php foreach ($foodtrucks as $foodtruck): ?>
      <div class="col-lg-3 col-md-6 col-sm-6 d-flex justify-content-center">
        <div class="card shadow Top8Card">
        <img src=
            <?php 
            if($foodtruck['Media'] != null){
              echo base_url("img/" . $foodtruck['Media']);
            }
            else{
              echo base_url("staticimg/FoodtruckStaticIcon.png");
            }         
            ?> 
            class="img-fluid card-img-top" alt="Food truck Photo">
          <div class="card-body">
            <h5 class="card-title"><?= $foodtruck['Name']; ?></h5>
            <p class="text-truncate"><?= $foodtruck['Description']?></p>
            <a href="<?= base_url("Foodtruckinfopage/" . $foodtruck['Name'])?>" class="btn btn-primary text-black bg-white border-black">Check it out!</a>
          </div>
        </div>  
      </div>
    <?php endforeach ?>
    </div>

    <div class="row" style="height: 75px">
      <div class="col text-center">
        <a href="Foodtruckspage" class="btn btn-primary text-black bg-white border-black shadow">View all foodtrucks</a>
      </div>
    </div>
 </div>


 <div class="container">
  <div class="row">
    <div class="col text-center">
      <h1>Upcoming Events</h1>
    </div>
  </div>
  <div class="row">

<?php foreach ($events as $event): ?>
        <div class="col-lg-6 col-md-6 col-sm-12 d-flex justify-content-center">
          <div class="card shadow EventCard">
            <div class="card-body">
              <h5 class="card-title"><?php echo $event['Header']?></h5>
              <p class="text-truncate"><?php echo $event['Description']?></p>
              <a href=<?= base_url('EventInfopage/' . $event['EventName'] . '/' . $event['Date'])?> class="btn btn-primary text-black bg-white border-black">Check it out!</a>
            </div>
          </div>
        </div>
<?php endforeach ?>
    
  </div>
  <div class="row" style="height: 75px">
    <div class="col text-center">
      <a href="Eventspage" class="btn btn-primary text-black bg-white border-black shadow">View all Events</a>
    </div>
  </div>
</div>  

<?php endif ?>  

<?php if(session('LoggedIn') == false): ?>
    <div class="row justify-content-center align-items-center text-center">
        <div class="col-lg-12 col-xs-4">
          <a href="Login" id="SearchButton" class="btn btn-primary text-white rounded-pill btn-lg border-black SearchFunctions bg-black">Login</a>

        </div>
      </div>
  </div>

<?php endif ?>


<?php if (session('LoggedIn') == true && session('UserType') == 'FO'): ?>
    </div>
<?php endif ?>




<div id="Sponsortab" class="container">
  <div class="row">
    <div class="col text-center">
      <h1>We use Daikoku!</h1>
    </div>
  </div>
  <div class="row">
    <div id="SponsorCol" class="col d-flex justify-content-center">
      <img src="<?=base_url("staticimg/uhasseltLogo.png")?>" style="width:200px" alt="Sponsor1">
    </div>
    <div class="col d-flex justify-content-center">
      <img src="<?=base_url("staticimg/NikeLogo.png")?>" class="border-white" style="width:200px"  alt="Sponsor2">
    </div>
    <div class="col d-flex justify-content-center">
      <img src="<?=base_url("staticimg/GoogleLogo.png")?>" style="width:200px" alt="Sponsor3">
    </div>
  </div>
 </div>
 


 <div id="InfoTab" class="container text-center">
  <h3>What is Daikoku and how does it work?</h3>
  <br>

  <div class="row">
    <div class="col-xxl-12 col-sm-12">
      <p class="text-white">
        Daikoku is a versatile platform that primarily 
        serves as a bridge between food truck owners and hungry consumers. For those who already own food trucks, Daikoku provides an opportunity to register their mobile kitchens, 
        making them accessible options for consumers seeking a unique culinary experience. 
        If you're a food lover, keep an eye out for Daikoku's diverse fleet of registered food trucks in your neighborhood. 
        These mobile kitchens offer a convenient way to enjoy a wide range of culinary delights on the go, from global fusion to creative spins on classics. 
        Get ready for a delightful curbside dining experience, courtesy of Daikoku.</p>
    </div>
  </div>
 </div>

 <div class="toast" role="alert" aria-live="assertive" aria-atomic="true">
  <div class="toast-body">
    Hello, world! This is a toast message.
    <div class="mt-2 pt-2 border-top">
      <button type="button" class="btn btn-primary btn-sm">Take action</button>
      <button type="button" class="btn btn-secondary btn-sm" data-bs-dismiss="toast">Close</button>
    </div>
  </div>
</div>
