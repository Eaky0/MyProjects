<?php
$FoodTruckInfo = $data[0];
$Categories = $data[1];
$Menus = $data[2];
?>

<div id="InstructionSection" class="container">
  <div class="row">
    <div class="col">
      <p class="d-inline-flex gap-1">
        <button class="btn bg-black border-black btn-primary SearchButton" type="button" data-bs-toggle="collapse" data-bs-target="#Instructions" aria-expanded="false" aria-controls="Instructions">
          Editor Guide
        </button>
      </p>
      <div class="collapse" id="Instructions">
        <div class="card card-body">
        <h5 class="mb-1">How does it work?</h5>
          Similar to a page that gives you information about a food truck, this editor page
          provides a simple interface for owners.
        <h5 class="mt-1">Unchangeable information</h5>
          <p>The following information can't be edited:</p>
          <ul>
            <li>The name of your foodtruck</li>
            <li>Your email-address</li>
          </ul>
          <h5 class="mb-1">Media</h5>
          Unlike text, images and videos are automatically saved when edited.
        </div>
      </div>
    </div>
  </div>
</div>

<div id="HeaderSection" class="container">
  <div id="SectionText" class="row">
    <div class="col text-center">
      <h1 class="display-1"><?= $FoodTruckInfo['Name']; ?></h1>
    </div>
  </div>
</div>

<div id="MainSection" class="container">
  <div class="row">
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
        <div class="col-12 text-white">
          <p class="mt-2">Images</p>
          <ul class="list-group overflow-auto" style="max-height: 160px;">
          <?php foreach ($FoodTruckInfo["Media"] as $Image): ?>
            <li class="list-group-item">
              <div class="row">
                <div class="col-12">
                  <label><?=$Image["FileName"]?></label>
                </div>
                <div class="col-12">
                  <form action=<?= base_url('Foodtruckeditorpage/DeleteMainImage')?> method="post" enctype="multipart/form-data">
                  <?= csrf_field() ?>  
                    <button class="btn bg-black PlusMinusIcon" type="submit" name="SelectedFile" value="<?= $Image['FileName']; ?>">
                        <i class="bi bi-dash-square"></i> 
                    </button>
                  </form>
                </div>
              </div>
            </li>
          <?php endforeach ?>
          </ul>
          <button class="btn bg-black text-white mt-2" data-bs-toggle="modal" data-bs-target="#addMainImages" style="font-family: impact; font-style: italic;">Add Images</button>
          <div class="modal fade" data-bs-backdrop="static" id="addMainImages" tabindex="-1" aria-labelledby="addMainImagesLabel" aria-hidden="true">
            <div class="modal-dialog modal-dialog-centered">
              <div class="modal-content">
                <div class="modal-header">                              
                  <h1 class="modal-title fs-5 text-black" id="addMainImagesLabel">Add Images</h1>
                </div>
                <div class="modal-body">          
                  <form action=<?= base_url('Foodtruckeditorpage/AddedMainImages')?> method="post" id="MainImagesForm" enctype="multipart/form-data">
                  <?= csrf_field() ?>
                  <input type="file" id="MainI" name="MainI[]" class="form-control" accept="image/*" multiple>

                  <div class="mt-2" id="AlertSection">
                    <!--
                        <div class="alert alert-danger">
                            <ul>
                            </ul>
                        </div>
                    -->
                  </div>
                </div>
                <div class="modal-footer">
                  <button id="CancelButton4" type="button" class="btn btn-danger" data-bs-dismiss="modal">Cancel</button>
                  <button onclick="mainMediaValidation(event)" class="btn btn-primary bg-black">Add</button>
                </div>
                  </form>
                </div>
              </div>
            </div> <!--Modal ends here! --> 
        </div>
      </div>

    </div>
    
    <div class="col-lg-6 col-md-12 text-white">
      <form action=<?= base_url('Foodtruckeditorpage/EditedMainSection')?> method="post" id="MainSectionForm">
      <?= csrf_field() ?>
      <label>Description header:</label>
      <textarea id="DescHeader" name="DescHeader" oninput="EnableSaveButton('SaveMain')" class="form-control" style="font-size: large; max-height:100px; font-style: italic;" rows="3"><?= $FoodTruckInfo['Header'];  ?></textarea>
      <label>Description body:</label>
      <textarea id="DescBody" name="DescBody" oninput="EnableSaveButton('SaveMain')" class="form-control" style="font-size: large; height:200px; max-height:400px; margin-top: 10px;  font-style: italic;"><?= $FoodTruckInfo['Description'];  ?></textarea>
      <div class="col-lg-4 col-md-12 m-2">
        <label>Country:</label>
        <input id="Country" name="Country" oninput="EnableSaveButton('SaveMain')" type="text" style="font-style: italic; font-size: large;" value="<?= $FoodTruckInfo["Country"] ?>" class="form-control">
      </div> 
      <div class="col-lg-4 col-md-12 m-2">
        <label>Kitchen:</label>
        <input id="KitchenType" name="KitchenType" oninput="EnableSaveButton('SaveMain')" type="text" style="font-style: italic; font-size: large;" value="<?= $FoodTruckInfo["Kitchen"]?>" class="form-control">
      </div>
      <div class="col-lg-4 col-md-12 m-2">
        <label>Vehicle:</label>
        <input id="VehicleType" name="VehicleType" oninput="EnableSaveButton('SaveMain')" type="text" style="font-style: italic; font-size: large;" value="<?= $FoodTruckInfo["Vehicle"]?>" class="form-control">
      </div>
      <div class="col-lg-4 col-md-12 m-2">
        <input class="form-check-input" id="Publish" name="isPublished" oninput="EnableSaveButton('SaveMain')" type="checkbox" <?= $FoodTruckInfo["Published"] ? 'checked' : '' ?>>
        <label class="form-check-label" for="Publish">Publish your page</label>
      </div>
      <div class="col-md-12 m-2 text-center">

        <div class="mt-2" id="AlertSection2">
          <!--
            <div class="alert alert-danger">
              <ul>
              </ul>
            </div>
          -->
        </div>
      </div>
      
      <div class="col-md-12 m-2 text-center">
        <button id="SaveMain" onclick="MainSectionValidation(event)" style="font-size: large;" class="btn btn-primary rounded-pill btn-lg bg-black border-black SearchFunctions Savebutton">Save</button>
      </div>
      </form>
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
          <p style="font-size: x-large"><?=$Rating ?>/5</p>
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
        <form action=<?= base_url('Foodtruckeditorpage/EditedContactSection')?> method="post" id="ContactSectionForm">
        <?= csrf_field() ?>
        <div class="text-white col-lg-2 col-sm-12 d-flex">
          <i id="PhoneIcon" class="bi bi-telephone-fill"></i>
          <input id="PhoneNumber" type="Tel" class="form-control" name="PhoneNumber" value="<?= $FoodTruckInfo['Tel']; ?>" oninput="EnableSaveButton('SaveContactInfo')" style="font-style:italic; font-family:Impact; margin-left:20px">
        </div>
        <div class="text-white col-lg-8 col-sm-12 ms-3 mb-3 mt-2">
          <label style="padding-left:30px;">Opening Time: <input id="OpeningTime" name="OpeningTime" oninput="EnableSaveButton('SaveContactInfo')" type="time"  class="form-control" value="<?= $FoodTruckInfo['OpenTime'];  ?>"></label>
          <label style="padding-left:30px;">Closing Time: <input id="ClosingTime" name="ClosingTime" oninput="EnableSaveButton('SaveContactInfo')" type="time" class="form-control" value="<?= $FoodTruckInfo['CloseTime'];  ?>"> </label>
        </div>
        <div class="text-white col-12 mb-4 d-flex">
          <i id="LocationIcon" class="bi bi-geo-alt-fill"></i>
          <label style="padding-left:20px;">Current: <input id="CurrentLocation" name="CurrentLocation" oninput="EnableSaveButton('SaveContactInfo')" value="<?= $FoodTruckInfo['CurrentLocation'];  ?>" type="text"  class="form-control" placeholder="Current Location"></label>
          <label style="padding-left:20px;">Next: <input id="NextLocation" name="NextLocation" oninput="EnableSaveButton('SaveContactInfo')" value="<?= $FoodTruckInfo['NextLocation'];  ?>" type="text" class="form-control" placeholder="Next Location"> </label>
        </div>
        <div class="text-white col-6 d-flex">
          <i id="EnvelopeIcon" class="bi bi-envelope-fill"></i>
          <h4 style="padding-left: 20px;"><?= $FoodTruckInfo['Email'];  ?></h4>
        </div>
        <div class="col-md-12 m-2 text-center">

          <div class="mt-2" id="AlertSection3">
            <!--
              <div class="alert alert-danger">
                <ul>
                </ul>
              </div>
            -->
          </div>
        </div>
        <div class="col-md-12 m-2 text-center">
          <button id="SaveContactInfo" onclick="ContactSectionValidation(event, '<?= $FoodTruckInfo['Name']; ?>')" style="font-size: large;" class="btn btn-primary rounded-pill btn-lg bg-black border-black SearchFunctions Savebutton">Save</button>
        </div>
        </form>
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
        <ul class="nav nav-pills">
          <li class="nav-item mx-2">
            <button class="btn bg-black PlusMinusIcon" data-bs-toggle="modal" data-bs-target="#newCategory"><i class="bi bi-plus-square"></i></button>
            <div class="modal fade" data-bs-backdrop="static" id="newCategory" tabindex="-1" aria-labelledby="newCategoryLabel" aria-hidden="true">
              <div class="modal-dialog modal-dialog-centered">
                <div class="modal-content">
                  <div class="modal-header">
                    <h1 class="modal-title fs-5" id="newCategoryLabel">New Category</h1>
                  </div>
                <div class="modal-body">
                  <form action=<?= base_url('Foodtruckeditorpage/AddedCategory')?> method="post" id="CategoryForm">
                      <?= csrf_field() ?>
                    <label for="Addcategory">Category Name:</label>
                    <input type="text" class="form-control" id="NewCategory" name="NewCategory">
                    
                    <div class="mt-2" id="AlertSection4">
                    <!--
                      <div class="alert alert-danger">
                        <ul>
                        </ul>
                      </div>
                    -->
                    </div>
                    </div>
                        <div class="modal-footer">
                        <button id="CancelButton1" type="button" class="btn btn-danger" data-bs-dismiss="modal">Cancel</button>
                        <button onclick="AddingCategoryValidation(event)" class="btn btn-primary bg-black">Add</button>
                    </div>
                  </form>
                </div>
              </div>
            </div>            
          </li>
          <?php if (!empty($Categories)): ?>
          <li class="nav-item mx-2">
            <button class="btn bg-black PlusMinusIcon" data-bs-toggle="modal" data-bs-target="#DeleteCategory"><i class="bi bi-dash-square"></i></button>
            <div class="modal fade" data-bs-backdrop="static" id="DeleteCategory" tabindex="-1" aria-labelledby="DeleteCategoryLabel" aria-hidden="true">
              <div class="modal-dialog modal-dialog-centered">
                <div class="modal-content">
                  <div class="modal-header">
                    <h1 class="modal-title fs-5" id="DeleteCategoryLabel">Delete Category</h1>
                  </div>
                <div class="modal-body">
                  <form action=<?= base_url('Foodtruckeditorpage/DeleteCategory')?> method="post" id="CategoryForm">
                      <?= csrf_field() ?>
                    <label>Select category:</label>
                    <select class="form-select" name="Category" required>
                    <?php for($index = 0; $index< count($Categories); ++$index):?>
                    <option><?=$Categories[$index]['Category']?></option>             
                    <?php endfor?>          
                    </select>
                    </div>
                        <div class="modal-footer">
                        <button type="button" class="btn btn-danger" data-bs-dismiss="modal">Cancel</button>
                        <button type="submit" class="btn btn-primary bg-black">Delete</button>
                    </div>
                  </form>
                </div>
              </div>
            </div>            
          </li>
          <?php endif ?>
        </ul>
      </nav>
    </div>

<?php if (!empty($Categories)): ?>
<div class="row bg-white col-10 m-2 rounded">


  <div class="col-lg-4 col-sm-12 m-2 justify-content-center align-items-center d-flex">
  <button class="btn bg-black text-white " data-bs-toggle="modal" data-bs-target="#addProduct" style="font-family: impact; font-style: italic;">Add new product</button>
  
  <div class="modal fade" data-bs-backdrop="static" id="addProduct" tabindex="-1" aria-labelledby="addProductLabel" aria-hidden="true">
    <div class="modal-dialog modal-dialog-centered">
      <div class="modal-content">
        <div class="modal-header">
          <h1 class="modal-title fs-5" id="addProductLabel">New product</h1>
        </div>
      <div class="modal-body">
        <form action=<?= base_url('Foodtruckeditorpage/AddedProduct')?> method="post" id="ProductForm" enctype="multipart/form-data">
          <?= csrf_field() ?>
          <label>Name:</label>
          <input type="text" class="form-control" id="NewProductName" name="NewProductName" required>
          <label>Price:</label>
          <input type="number" class="form-control" id="NewProductPrice" name="NewProductPrice" required>
          <label>Description:</label>
          <textarea type="text" class="form-control" id="NewProductDescription" name="NewProductDescription" required></textarea>
          <label>Ingredients:</label>
          <textarea type="text" class="form-control" id="NewProductIngredients" name="NewProductIngredients"required></textarea>
          <label>Allergenes:</label>
          <textarea class="form-control" id="NewProductAllergenes" name="NewProductAllergenes" required></textarea>
          <label>Category:</label>
          <select class="form-select" name="NewProductCategory" required>
          <?php for($index = 0; $index< count($Categories); ++$index):?>
            <option><?=$Categories[$index]['Category']?></option>             
          <?php endfor?>          
          </select>
          <label>Images and Videos:</label>
          <input type="file" id="NewProductIV" name="NewProductIV[]" class="form-control" accept="image/*,video/*" multiple>
          
          <div class="mt-2" id="AlertSection5">
          <!--
            <div class="alert alert-danger">
              <ul>
              </ul>
            </div>
          -->
          </div>

          </div>
              <div class="modal-footer">
              <button id="CancelButton2" type="button" class="btn btn-danger" data-bs-dismiss="modal">Cancel</button>
              <button onclick="CheckNewProductValidation(event)" class="btn btn-primary bg-black">Add product</button>
          </div>
        </form>
      </div>
    </div>
  </div>
</div>

<?php if (!empty($Menus)): ?>
  <div class="col-lg-3 col-sm-12 m-2 justify-content-center align-items-center d-flex">    
  <button class="btn bg-black text-white" data-bs-toggle="modal" data-bs-target="#addIV" style="font-family: impact; font-style: italic;">Add Image/Video</button>
  <div class="modal fade" data-bs-backdrop="static" id="addIV" tabindex="-1" aria-labelledby="addIVLabel" aria-hidden="true">
    <div class="modal-dialog modal-dialog-centered">
      <div class="modal-content">
        <div class="modal-header">                              
          <h1 class="modal-title fs-5" id="addIVLabel">Add Images/Videos</h1>
        </div>
        <div class="modal-body">          
          <form action=<?= base_url('Foodtruckeditorpage/AddedImagesVideos')?> method="post" id="IVForm" enctype="multipart/form-data">
          <?= csrf_field() ?>
          <label>Select product:</label>
          <select class="form-select mb-2" name="MenuName" required>
          <?php for($index = 0; $index< count($Menus); ++$index):?>
            <option><?=$Menus[$index]['Name']?></option>             
          <?php endfor?>          
          </select>
          <input type="file" id="ProductIV" name="ProductIV[]" class="form-control" accept="image/*,video/*" multiple>

          <div class="mt-2" id="AlertSection6">
          <!--
            <div class="alert alert-danger">
              <ul>
              </ul>
            </div>
          -->
          </div>

          </div>
              <div class="modal-footer">
              <button id="CancelButton3" type="button" class="btn btn-danger" data-bs-dismiss="modal">Cancel</button>
              <button onclick="MenuMediaValidation(event)" class="btn btn-primary bg-black">Add</button>
        </div>
        </form>
      </div>
    </div>
    </div> <!--Modal ends here! --> 
    </div>

    <div class="col-lg-4 col-sm-12 m-2 justify-content-center align-items-center d-flex">    
    <button class="btn btn-danger text-white"  data-bs-toggle="modal" data-bs-target="#DeleteProduct" style="font-family: impact; font-style: italic;">Delete Product</button>
    <div class="modal fade" data-bs-backdrop="static" id="DeleteProduct" tabindex="-1" aria-labelledby="DeleteProductLabel" aria-hidden="true">
    <div class="modal-dialog modal-dialog-centered">
      <div class="modal-content">
        <div class="modal-header">                              
          <h1 class="modal-title fs-5" id="DeleteProductLabel">Delete product</h1>
        </div>
        <div class="modal-body">          
          <form action=<?= base_url('Foodtruckeditorpage/DeleteProduct')?> method="post" id="DeleteProductForm" enctype="multipart/form-data">
          <?= csrf_field() ?>
          <label>Select product:</label>
          <select class="form-select mb-2" name="MenuName" required>
          <?php for($index = 0; $index< count($Menus); ++$index):?>
            <option><?=$Menus[$index]['Name']?></option>             
          <?php endfor?>          
          </select>
          </div>
              <div class="modal-footer">
              <button type="button" class="btn btn-danger" data-bs-dismiss="modal">Cancel</button>
              <button type="submit" class="btn btn-primary bg-black">Delete</button>
        </div>
        </form>
      </div>
    </div>
    </div> <!--Modal ends here! --> 
    </div>
<?php endif ?>
  </div>
<?php endif ?>

    <div data-bs-target="#Menubar" data-bs-spy="scroll" data-bs-root-margin="0px 0px -40%" data-bs-smooth-scroll="true" class="overflow-auto scrollspy-example bg-body-tertiary p-3 rounded" style="height: 800px;" tabindex="0">
    
    <?php for($index = 0; $index< count($Categories); ++$index):?>
      <h4 class="p-2" id=<?= "Category" . $index; ?> ><?= $Categories[$index]['Category'];?></h4>
      <?php for($index2 = 0; $index2< count($Menus); ++$index2):?> 
        <?php if($Categories[$index]['Category'] == $Menus[$index2]['Category']): ?>     
        <div id="MenuCard" class="card">
          <div class="row">
            <div class="col-lg-12 col-sm-12">
              <div class="row">
                <div class="col-lg-10 col-md-12 mt-2">
                <button class="btn bg-black text-white " data-bs-toggle="modal" data-bs-target="#EditProduct<?=$index2?>" style="font-family: impact; font-style: italic;">Edit product</button>
  
                <div class="modal fade" data-bs-backdrop="static" id="EditProduct<?=$index2?>" tabindex="-1" aria-labelledby="EditProductLabel<?=$index2?>" aria-hidden="true">
                  <div class="modal-dialog modal-dialog-centered">
                    <div class="modal-content">
                      <div class="modal-header">
                        <h1 class="modal-title fs-5" id="EditProductLabel<?=$index2?>">Edit product</h1>
                      </div>
                    <div class="modal-body">
                      <form action=<?= base_url('Foodtruckeditorpage/EditedMenuInfo')?> method="post" id="EditProductForm<?= $index2 + 1 ?>" enctype="multipart/form-data">
                        <?= csrf_field() ?>
                        <input type="hidden" name="MenuName" value="<?= $Menus[$index2]['Name']?>">
                        <label>Name:</label>
                        <input type="text" class="form-control" id="ProductName<?= $index2 + 1?>" name="ProductName" value="<?= $Menus[$index2]['Name']?>" required>
                        <label>Price:</label>
                        <input type="number" class="form-control" id="ProductPrice<?= $index2  + 1?>" name="ProductPrice" value="<?= $Menus[$index2]['Price']?>" required>
                        <label>Description:</label>
                        <textarea type="text" class="form-control" id="ProductDescription<?= $index2 + 1?>" name="ProductDescription" required><?= $Menus[$index2]['Description']?></textarea>
                        <label>Ingredients:</label>
                        <textarea class="form-control" id="ProductIngredients<?= $index2 + 1?>" name="ProductIngredients" required><?= $Menus[$index2]['Ingredients']?></textarea>
                        <label>Allergenes:</label>
                        <textarea class="form-control" id="ProductAllergenes<?= $index2 + 1?>" name="ProductAllergenes" required><?= $Menus[$index2]['Allergenes']?></textarea>
                        <label>Category:</label>
                        <select class="form-select" name="ProductCategory" value="<?= $Menus[$index2]['Category']?>" required>
                        <?php for($index4 = 0; $index4< count($Categories); ++$index4):?>
                          <option><?=$Categories[$index4]['Category']?></option>             
                        <?php endfor?>          
                        </select>
                        <div class="mt-2" id="AlertSection<?= 7 + $index2 ?>">
                        <!--
                          <div class="alert alert-danger">
                            <ul>
                            </ul>
                          </div>
                        -->
                        </div>
                        </div>
                            <div class="modal-footer">
                            <button onclick="Resetform5(<?= count($Menus)?>)" type="button" class="btn btn-danger" data-bs-dismiss="modal">Cancel</button>
                            <button onclick="EditProductValidation(event, <?= $index2 + 1?>, '<?=$Menus[$index2]['Name']?>')" class="btn btn-primary bg-black">Adjust Changes</button>
                        </div>
                      </form>
                    </div>
                  </div>
                </div>


                </div>
                <div class="col-lg-10 col-md-12 mt-2">
                  <h4 style="font-size: x-large;  font-style: italic; margin-bottom:20px;"><?= $Menus[$index2]['Name']?></h4>
                </div>
              </div> 
            </div>
            <div class="col-12 d-flex">
              <div class="input-group">
                <h4 style="font-size: x-large;  font-style: italic; margin-bottom:20px;">€ <?= $Menus[$index2]['Price']?></h4>
              </div>
            </div>
            <div class="col-12 mt-2">
              <p>
                <button class="btn btn-primary bg-black border-black" type="button" data-bs-toggle="collapse" data-bs-target=<?="#collapse" . $index2; ?> aria-expanded="false" aria-controls="<?="collapse" . $index2; ?>">
                  More Info
                </button>
              </p>
              <div class="collapse" id="<?="collapse" . $index2; ?>">
                <div class="row">
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
                                                </div >';
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
                      <div class="col-12">
                        <p class="mt-2">Images & Video's</p>
                        <?php if(!empty($MenuMedia)): ?>
                        <ul class="list-group overflow-auto" style="max-height: 160px;">
                        <form method="post" action="<?= base_url("Foodtruckeditorpage/DeleteImagesVideos")?>">
                          <?=csrf_field()?>
                            <input type="hidden" name="MenuName" value="<?= $Menus[$index2]['Name']?>">
                            <ul class="list-group">
                                <?php for ($index3 = 0; $index3 < count($MenuMedia); ++$index3) : ?>
                                    <li class="list-group-item">
                                        <div class="row">
                                            <div class="col-12">
                                                <p><?= $MenuMedia[$index3]['FileName']; ?></p>
                                            </div>
                                            <div class="col-12">
                                                <button class="btn bg-black PlusMinusIcon" type="submit" name="SelectedFile" value="<?= $MenuMedia[$index3]['FileName']; ?>">
                                                    <i class="bi bi-dash-square"></i> 
                                                </button>
                                            </div>
                                        </div>
                                    </li>
                                <?php endfor ?>
                            </ul>
                        </form>
                        </ul> 
                        <?php else: ?>
                        <p>This menu does not have any pictures</p>
                        <?php endif?>
                      </div>
                    </div>
                  </div>
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
              </div>
            </div>
            <div class="col-md-12 m-2 text-center">
            </div>
          </div>
        </div>
        <?php endif ?>
        <?php endfor ?>
        <?php endfor ?>
    </div>
  </div>
</div>
