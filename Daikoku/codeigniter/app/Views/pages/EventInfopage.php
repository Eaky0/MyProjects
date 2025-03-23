<?php
$EventInfo = $data[0];
$EventFoodTrucks = $data[1];
?>


<div id="HeaderSection" class="container">
  <div id="SectionText" class="row">
    <div class="col text-center">
      <h1 class="display-1"><?=$EventInfo['EventName']?></h1>
      <h3><?php 
          $dateString = $EventInfo["Date"];
          $date = new DateTime($dateString);
          $formattedDate = $date->format('F jS, Y');
          echo $formattedDate;?></h3>
    </div>
  </div>
</div>

<div id="MainSection" class="container">
  <div class="row">
    <div class="text-white text-center">
      <h4><?= $EventInfo['Header']?></h4>
      <p><?= $EventInfo['Description']?></p>
    </div>
  </div>
</div>

<div id="ScheduleSection" class="container p-3">
  <div class="row">
    <div class="col-12 text-center text-white">
      <h1 class="display-6">Schedule</h1>
      <p>Here, you can see information about our schedule.</p>
    </div>
    <div class="col">
      <div id="ContactSourceSection" class="row">
        <div class="text-white col-lg-4 col-sm-12 d-flex">
          <i id="ClockIcon" class="bi bi-clock-fill"></i>
          <h4 style="padding-left: 20px;" class="text-center">
          <?php 
          $dateString = $EventInfo['StartTime']; // Replace this with your date/time string
          $date = new DateTime($dateString);
          
          $formattedTime = $date->format('H:i'); // 'H' for 24-hour format, 'i' for minutes
          echo $formattedTime;?>
          
          -
          <?php 
          $dateString = $EventInfo['EndTime']; // Replace this with your date/time string
          $date = new DateTime($dateString);
          $formattedTime = $date->format('H:i'); // 'H' for 24-hour format, 'i' for minutes
          echo $formattedTime;
          
          ?></h4>
        </div>
        <div  class="text-white col-12 d-flex">
          <i id="CalendarIcon" class="bi bi-calendar2-check-fill"></i>
          <h4 style="padding-left:20px;">Food trucks:</h4>
        </div>
        <div  class="text-white col-12 d-flex">
          <div id= "AvailableFoodTrucksList" class="row">

          <?php foreach ($EventFoodTrucks as $FoodTruck): ?>
            <div class="col-lg-3 col-md-6 col-sm-6 d-flex justify-content-center">
        <div class="card shadow FoodTruckCard">
        <img src=
            <?php 
            if($FoodTruck['Media'] != null){
              echo base_url("img/" . $FoodTruck['Media']);
            }
            else{
              echo base_url("staticimg/FoodtruckStaticIcon.png");
            }         
            ?> 
            class="img-fluid card-img-top" alt="Food truck Photo">
          <div class="card-body">
            <h5 class="card-title"><?= $FoodTruck['Name']; ?></h5>
            <a href="<?= base_url("Foodtruckinfopage/" . $FoodTruck['Name'])?>" class="btn btn-primary text-black bg-white border-black">Check it out!</a>
          </div>
        </div>  
      </div>
          <?php endforeach ?>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>