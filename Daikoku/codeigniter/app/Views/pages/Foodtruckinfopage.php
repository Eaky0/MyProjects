<?php
$FoodTruckInfo = $data[0];
$Categories = $data[1];
$Menus = $data[2];
?>


<div id="HeaderSection" class="container">
  <div id="SectionText" class="row">
    <div class="col text-center">
      <h1 class="display-1"><?= $FoodTruckInfo['Name']; ?></h1>
    </div>
  </div>
</div>

<div id="MainSection" class="container">
  <div class="row">
    <?php if($FoodTruckInfo['Media'] != null): ?>
    <div class="col-lg-6 col-md-12 pb-2">
      <div id="MainSectionImageEditor" class="row">
        <div class="col-lg-12">
          <div class="carousel slide" data-bs-ride="carousel">
            <div class="carousel-inner">
            <?php 
                foreach ($FoodTruckInfo["Media"] as $index => $Image) {
                $FileName = $Image['FileName'];
                $FileExtension = pathinfo($FileName, PATHINFO_EXTENSION);
                $isActive = ($index === 0) ? ' active' : '';

                $imageExtensions = ['jpg', 'jpeg', 'png', 'gif', 'bmp'];

                if (in_array(strtolower($FileExtension), $imageExtensions)) {
                    echo '<div class="carousel-item' . $isActive . '">
                            <img src="' . base_url('img/'. $FileName) . '" class="img-fluid rounded d-block MainImageFormat" alt="' . $FileName . '">
                          </div>';
                } else {
                    echo '<div class="carousel-item' . $isActive . '">
                            <img src="Browser doesn\'t support extension" class="d-block MainImageFormat" alt="' . $FileName . '">
                          </div>';
                  }
                }?>
            </div>
          </div>
        </div>
      </div>
    </div>
    <?php endif ?>
    <div class="col-lg-6 col-md-12 text-white">
      <h4><?= $FoodTruckInfo['Header'];  ?></h4>
      <div><?= $FoodTruckInfo['Description'];  ?></div>
      <div class="col-lg-6 col-md-12 mt-2">
      <h4>Country: <p><?= $FoodTruckInfo["Country"] ?></p></h4>
      </div>
      <div class="col-lg-6 col-md-12 mt-2">
      <h4>Kitchen: <p><?= $FoodTruckInfo["Kitchen"] ?></p></h4>
      </div>
      <div class="col-lg-6 col-md-12 mt-2">
      <h4>Vehicle: <p><?= $FoodTruckInfo["Vehicle"] ?></p></h4>
      </div>
      <div class="row mt-3">
        <div class="col-lg-3 col-md-12">
          <h4 style="font-size: xx-large;">Rating:</h4>
        </div>
        <div class="col-lg-4 col-md-12">
        <?php
        
        $Rating = $FoodTruckInfo['Rating']; 

        //Calculating rating stars. Always rounded
        $FullStars = intdiv(round($Rating * 2) ,2);
        $HalfStars = round($Rating * 2) - ($FullStars * 2);

        //Adding Full stars.
        for ($index = 0; $index < $FullStars; ++$index){
           echo "<i class=\"bi bi-star-fill RatingStar\"></i>";
        }
        
        if ($HalfStars > 0){
          //Adding Halfstars.
          for ($index = 0; $index < $HalfStars; ++$index){
            echo "<i class=\"bi bi-star-half RatingStar\"></i>";
          }

          //Empty fill for the remaining stars depending on the amount of full- and halfstars.
          for ($index = 0; $index < (5 - ($FullStars + $HalfStars)); ++$index){
            echo "<i class=\"bi bi-star RatingStar\"></i>";
          }
        }
        else{
          //Adding remaing empty stars.
          for ($index = 0; $index < (5-$FullStars); ++$index){
            echo "<i class=\"bi bi-star RatingStar\"></i>";
          }
        }
        ?>
        </div>
        <div class="col-lg-2 col-md-12">
          <p style="font-size: xx-large"><?=$Rating ?>/5</p>
        </div>
      </div>
    </div>
  </div>
</div>

<div id="ContactSection" class="container p-3">
  <div class="row">
    <div class="col-12 text-center text-white">
      <h1 class="display-6">Contact information</h1>
    </div>
  

    <div class="col">
      <div id="ContactSourceSection" class="row">
        <div class="text-white col-lg-4 col-sm-12 d-flex">
          <i id="PhoneIcon" class="bi bi-telephone-fill"></i>
          <h4 style="padding-left: 20px;"><?= $FoodTruckInfo['Tel']; ?></h4>
        </div>
        <div class="text-white col-lg-8 col-sm-12 ms-3 mb-3">
          <label style="padding-left:30px;">Opening time: <h4>
          <?php 
          $Timestring = $FoodTruckInfo['OpenTime'];
          $timeOnly = date('H:i', strtotime($Timestring));
          echo $timeOnly;
          ?></h4></label>
          <label style="padding-left:30px;">Closing time: <h4><?php
          $Timestring = $FoodTruckInfo['CloseTime'];
          $timeOnly = date('H:i', strtotime($Timestring));
          echo $timeOnly;
           ?></h4></label>
        </div>  
        <div class="text-white col-12 mb-4 d-flex">
          <i id="LocationIcon" class="bi bi-geo-alt-fill"></i>
          <label style="padding-left:20px;">Current: <h4><?= $FoodTruckInfo['CurrentLocation'];?></h4></label>
          <label style="padding-left:20px;">Next: <h4><?= $FoodTruckInfo['NextLocation'];?></h4></label>
        </div>
        <div class="text-white col-12 mb-4 d-flex">
          <i id="EnvelopeIcon" class="bi bi-envelope-fill"></i>
          <h4 style="padding-left: 20px;"><?= $FoodTruckInfo['Email'];  ?></h4>
        </div>
        <div class="text-white col-6 d-flex">
          <i id="ChatIcon" class="bi bi-chat-dots-fill"></i>
          <a style="margin-left: 20px;" href="<?= base_url("Chatpage/" . $FoodTruckInfo["Name"]) ?>" class="btn btn-primary rounded-pill bg-black border-black SearchFunctions">Chat with us!</a>
        </div>
      </div>
    </div>
  </div>
</div>

<div id="MenuSection" class="container">
  <div class="row">
    <div class="col-12 text-center ">
      <h1 class="display-6">Menu's</h1>
    </div>
    <div class="col-12">
      <nav id="Menubar" class="rounded navbar bg-white px-3">
        <ul class="nav nav-pills overflow-auto">

<?php for($index = 0; $index< count($Categories); ++$index):?>
          <li class="nav-item m-2">
            <a class="nav-link bg-white" href=<?= "#Category" . $index; ?>><div class="p text-black"><?=$Categories[$index]['Category']?></div></a>
          </li>
<?php endfor ?>
        </ul>
      </nav>
    </div>
    <div data-bs-target="#Menubar" data-bs-spy="scroll" data-bs-root-margin="0px 0px -40%" data-bs-smooth-scroll="true" class="overflow-auto scrollspy-example bg-body-tertiary p-3 rounded" style="height: 800px;" tabindex="0">
    
    <?php for($index = 0; $index< count($Categories); ++$index):?>
      <h4 class="p-2" id=<?= "Category" . $index; ?> ><?= $Categories[$index]['Category'];?></h4>
      <?php for($index2 = 0; $index2< count($Menus); ++$index2):?> 
        <?php if($Categories[$index]['Category'] == $Menus[$index2]['Category']): ?>     
        <div class="card MenuCard">
          <div class="row">
            <form action=<?=base_url("Foodtruckinfopage/" . $FoodTruckInfo['Name'] . "/AddedToShoppingCart")?> method="post">
            <?= csrf_field() ?>
            <div class="col-lg-12 col-md-12">
              <input type="hidden" name="ProductName" value="<?= $Menus[$index2]['Name']?>">
              <h4 style="font-size: x-large;  font-style: italic; margin-bottom:20px;"><?= $Menus[$index2]['Name']?></h4>
            </div>
            <div class="col-lg-12 col-md-12 mt-2">
             <input type="hidden" name="ProductPrice" value="<?= $Menus[$index2]['Price']?>">
             <h4 style="font-size: x-large;  font-style: italic; margin-bottom:20px;">€ <?= $Menus[$index2]['Price']?></h4>
            </div>
            <div class="col-lg-3 col-md-4 d-sm-flex">
              <input min="1" value="1" type="number" name="ProductAmount" class="form-control mt-2">
              <button type="submit" class="btn bg-black ShoppingIcon ms-sm-2 mt-2"><i class="bi bi-cart-fill "></i></button>
            </div>
            </form>
            <div class="col-12 mt-2">
              <p>
                <button onclick="ResetForm(<?= $index2 ?>)"class="btn btn-primary bg-black border-black" type="button" data-bs-toggle="collapse" data-bs-target=<?="#collapse" . $index2; ?> aria-expanded="false" aria-controls="<?="collapse" . $index2; ?>">
                  More Info
                </button>
              </p>
              <div class="collapse" id="<?="collapse" . $index2; ?>">
                <div class="row">
                <?php if ($Menus[$index2]['Media'] != null):?>
                  <div class="col-lg-6 col-md-12">
                    <div class="row">
                      <div class="col-lg-12">
                        <div id="Category<?= $index ?>Item<?= $index2 ?>" class="carousel slide">
                            <div class="carousel-inner">
                                <?php 

                                    $MenuMedia = $Menus[$index2]['Media'];
                                    foreach ($MenuMedia as $index3 => $media) {
                                    $FileName = $media['FileName'];
                                    $FileExtension = pathinfo($FileName, PATHINFO_EXTENSION);
                                    $isActive = ($index3 === 0) ? ' active' : '';

                                    $imageExtensions = ['jpg', 'jpeg', 'png', 'gif', 'bmp'];
                                    $videoExtensions = ['mp4', 'webm', 'avi', 'mov', 'mkv'];

                                    if (in_array(strtolower($FileExtension), $imageExtensions)) {
                                        echo '<div class="carousel-item' . $isActive . '">
                                                <img src="' . base_url('img/'. $FileName) . '" class="img-fluid rounded d-block MenuImageFormat" alt="' . $FileName . '">
                                              </div>';
                                    } elseif (in_array(strtolower($FileExtension), $videoExtensions)) {
                                        echo '<div class="carousel-item' . $isActive . '">
                                                <video class="img-fluid rounded MenuImageFormat" controls muted>
                                                    <source src="' . base_url("img/" . $FileName) . '" type="video/mp4">
                                                </video>
                                              </div>';
                                    } else {
                                        echo '<div class="carousel-item' . $isActive . '">
                                                <img src="Browser doesn\'t support extension" class="d-block MenuImageFormat" alt="' . $FileName . '">
                                              </div>';
                                    }
                                }
                                ?>
                            </div>
                            <?php if (count($MenuMedia) > 1) : ?>
                                <button class="carousel-control-prev" type="button" data-bs-target="#Category<?= $index ?>Item<?= $index2 ?>" data-bs-slide="prev">
                                    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                                    <span class="visually-hidden bg-black">Previous</span>
                                </button>
                                <button class="carousel-control-next" type="button" data-bs-target="#Category<?= $index ?>Item<?= $index2 ?>" data-bs-slide="next">
                                    <span class="carousel-control-next-icon" aria-hidden="true"></span>
                                    <span class="visually-hidden bg-black">Next</span>
                                </button>
                            <?php endif; ?>
                          </div>
                      </div>
                    </div>
                  </div>
                  <?php endif ?>
                  <div class="col-lg-6 col-md-12">
                      <h4>
                        About this menu:
                      </h4>
                      <p><?= $Menus[$index2]['Description']?></p>
                      <br>
                      <h4>
                        Ingredients:
                      </h4>
                      <p><?= $Menus[$index2]['Ingredients']?></p>
                      <br>
                      <h4>Allergenes:</h4>
                      <p><?= $Menus[$index2]['Allergenes']?></p>
                  </div>
                </div>
                <div class="row p-2">
                  <div class="col-12 text-center">
                    <h1>Reviews</h1>
                  </div>
                  <div class="col-12">
                    <div id="ReviewSection" style="height:250px;" class="overflow-auto bg-body-tertiary p-2 rounded" tabindex="0">
                      <?php $MenuReviews = $Menus[$index2]['Reviews']; foreach($MenuReviews as $Review): ?>
                      <div class="card p-2 m-2">
                        <div class="row">
                          <div class="col-lg-6 col-md-12 float-right">
                            <div class="row">
                              <div class="col-12">
                                <p class="text-grey">
                                <?php
                                  $timestamp = $Review['Timestamp'];
                                  $formattedTime = date('m/d/Y h:i A', strtotime($timestamp));
                                  echo $formattedTime;
                                  ?>
                                </p>
                              </div>
                              <div class="col-12">
                                <div class="h6"><?= $Review['User']?></div>
                              </div>
                              <div class="col-12">
                                <div class="p"><?= $Review['Review']?></div>
                              </div>
                              <div class="col-12">
                                <div class="col-lg-5 col-md-12">
                                <?php
                                  $Rating = $Review['Rating']; 

                                  //Calculating rating stars. Always rounded
                                  $FullStars = intdiv(round($Rating * 2) ,2);
                                  $HalfStars = round($Rating * 2) - ($FullStars * 2);

                                  //Adding Full stars.
                                  for ($i = 0; $i < $FullStars; ++$i){
                                      echo "<i class=\"bi bi-star-fill RatingStar\"></i>";
                                  }
                                  
                                  if ($HalfStars > 0){
                                    //Adding Halfstars.
                                    for ($i = 0; $i < $HalfStars; ++$i){
                                      echo "<i class=\"bi bi-star-half RatingStar\"></i>";
                                    }

                                    //Empty fill for the remaining stars depending on the amount of full- and halfstars.
                                    for ($i = 0; $i < (5 - ($FullStars + $HalfStars)); ++$i){
                                      echo "<i class=\"bi bi-star RatingStar\"></i>";
                                    }
                                  }
                                  else{
                                    //Adding remaing empty stars.
                                    for ($i = 0; $i < (5-$FullStars); ++$i){
                                      echo "<i class=\"bi bi-star RatingStar\"></i>";
                                    }
                                  }
                                  ?>
                                </div>
                              </div>
                            </div>
                          </div>
                        </div> 
                      </div>
                    <?php endforeach ?>
                    </div>
                  </div>
                  <div class="col">
                    <div class="row p-2 rounded">
                      <form action="<?= base_url('Foodtruckinfopage/'. $FoodTruckInfo['Name'] . '/ReviewWritten'); ?>" id="ReviewForm<?= $index2 ?>" method="post">
                      <?= csrf_field() ?>
                      <input type="hidden" name ="MenuName" value="<?= $Menus[$index2]['Name'] ?>">
                        <div class="col-lg-12 col-md-12 p-2">
                          <textarea class="form-control" placeholder="Lorem Ipsum..." rows="3" id="ReviewText<?= $index2 ?>"name="ReviewText"></textarea>
                        </div>
                        <div class="col-lg-12 col-md-12 p-2">
                          <select class="form-select" id="Rating<?=$index2?>" name="Rating">
                            <option label="No Rating" required></option>
                            <option>0.5</option>
                            <option>1</option>
                            <option>1.5</option>
                            <option>2</option>
                            <option>2.5</option>
                            <option>3</option>
                            <option>3.5</option>
                            <option>4</option>
                            <option>4.5</option>
                            <option>5</option>
                          </select>
                        </div>

                        <div class="col-lg-lg-12 col-md-12 p-2">
                          <div class="mt-2" id="AlertSection<?= $index2 ?>">
                            <!--
                            <div class="alert alert-danger">
                              <ul>
                              </ul>
                            </div>
                            -->
                          </div>
                        </div>
                        <div class="col-lg-3 col-sm-12 p-2">
                          <button class="form-control btn btn-primary btn-lg bg-black text-white border-black SearchFunctions" onclick="CheckReview(<?= $index2 ?>, event)">Send review</button>
                        </div>
                      </form>
                    </div>
                  </div>
                </div>

              </div>
            </div>
          </div>
        </div>
        <?php endif?>
        <?php endfor ?>
        <?php endfor ?>
    </div>
  </div>
</div>