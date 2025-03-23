    <div id="HeaderSection" style="background-image: url('staticimg/EventsBackground.jpg');" class="container">
      <div id="SectionText" class="row">
        <div class="col text-center">
          <h1 class="display-1 text-white">Events</h1>
        </div>
      </div>
    </div>

    <div id="IntroSection" class="container">
      <div id="IntroText" class="row">
        <div class="col-lg-12 text-center">
          <h1>Where the party roars, Daikoku soars!</h1>
          <p>Our foodtrucks are ready steady at famous festival events!</p><p> Don't miss out our delicious meals, while you are partying!</p> <p>The section below shows all the events, in which you can spot us!</p>
        </div>
      </div>
    </div>


    <div id="UpcomingEventsSection" class="container">
      <div class="row">
        <div id="UpcomingEventsText" class="col text-center">
          <h1>Upcoming Events</h1>
        </div>
      </div>
      <div class="row">

<?php foreach ($upcomingEvents as $upcomingEvent): ?>
        <div class="col-lg-6 col-md-6 col-sm-12 d-flex justify-content-center">
          <div class="card shadow EventCard">
            <div class="card-body">
              <h5 class="card-title"><?php echo $upcomingEvent['Header']?></h5>
              <p class="text-truncate"><?php echo $upcomingEvent['Description']?></p>
              <a href=<?= base_url('EventInfopage/' . $upcomingEvent['EventName'] . '/' . $upcomingEvent['Date'])?> class="btn btn-primary text-black bg-white border-black">Check it out!</a>
            </div>
          </div>
        </div>
<?php endforeach ?>
      </div>
    </div>


    <div id="PreviousEventsSection" class="container">
      <div class="row">
        <div id="PreviousEventsText" class="col text-center">
          <h1>Previous Events</h1>
        </div>
      </div>
      <div class="row">

<?php foreach ($previousEvents as $previousEvent): ?>
        <div class="col-lg-6 col-md-6 col-sm-12 d-flex justify-content-center">
          <div class="card shadow EventCard">
            <div class="card-body">
              <h5 class="card-title"><?php echo $previousEvent['Header']?></h5>
              <p class="text-truncate"><?php echo $previousEvent['Description']?></p>
              <a href="EventInfopage/<?=$previousEvent['EventName']?>/<?=$previousEvent['Date']?>" class="btn btn-primary text-black bg-white border-black">Check it out!</a>
            </div>
          </div>
        </div>
<?php endforeach ?>
      </div>
    </div> 