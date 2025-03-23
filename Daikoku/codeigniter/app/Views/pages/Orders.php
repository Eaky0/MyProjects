<div id="HeaderSection" class="container">
  <div id="SectionText" class="row">
    <div class="col text-center">
      <h1 class="display-1">
      <?php   
      
      if (session("UserType") == 'C'){
        echo 'My orders';
      }
      else{
        echo 'Received orders';
      }
      ?>
      </h1>
    </div>
  </div>
</div>

<div id="OrderSection" class="container">
  <div class="row">
<?php if(!empty($Orders)): ?>
    <div class="col-12 text-white">
      <h1>Orders</h1>
    </div>
    <div class="table-responsive col-12">
      <table class="table">
        <thead>
          <tr>
            <th scope="col">Order number</th>
            <th scope="col"></th>
            <th scope="col">Order time</th>
            <th scope="col">Pick up time</th>
            <th scope="col">Total price</th>
            <th scope="col">
            <?php  
            if (session("UserType") == "C"){
                echo 'Ordered at';
            }
            else{
                echo 'Ordered by';
            }
            ?></th>
            <th scope="col">Status</th>
            <?php if (session("UserType") == 'FO'): ?>
            <th></th>
            <?php endif ?>
          </tr>
        </thead>
        <tbody>
<?php foreach($Orders as $index => $Order): ?>
            <tr>
               <th scope="row"><?= $Order["Order_ID"]?></th>
               <td>
                <button class="btn btn-primary border-black bg-black" style="font-style:italic; font-family:impact;" type="button" data-bs-toggle="modal" data-bs-target="#Products<?=$index?>" aria-expanded="false">Products</button>
                <div class="modal fade" id="Products<?= $index ?>" tabindex="-1" aria-labelledby="ProductsLabel<?=$index?>" aria-hidden="true">
                  <div class="modal-dialog modal-dialog-centered">
                    <div class="modal-content">
                      <div class="modal-header">
                        <h5 class="modal-title" id="ProductsLabel<?= $index ?>" >Order <?=$Order["Order_ID"] ?></h5>
                        <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                      </div>
                      <div class="modal-body">
                        <table class="table">
                          <thead>
                            <tr>
                              <th scope="col">#</th>
                              <th scope="col">Product</th>
                              <th scope="col">Price</th>
                              <th scope="col">Amount</th>
                            </tr>
                          </thead>
                          <tbody>
                        <?php foreach($Order['Products'] as $index2 => $Product): ?>
                            <tr>
                              <th scope="row"><?= $index2 + 1 ?></th>
                              <td><?= $Product['ProductName'] ?></td>
                              <td>€ <?= $Product['ProductPrice'] ?></td>
                              <td><?= $Product['Amount'] ?></td>
                            </tr>
                        <?php endforeach ?>
                          </tbody>
                        </table>
                      </div>
                      <div class="modal-footer">
                        <button type="button" class="btn btn-danger" data-bs-dismiss="modal">Close</button>
                      </div>
                    </div>
                  </div>
                </div>                
              </td>
              <td>
              <?php 
              $Timestring = $Order["OrderTime"];
              $TimeFormat = date('m/d/Y h:i A', strtotime($Timestring));
              $PickedUp = $Order["PickedUp"];
              echo $TimeFormat;
              ?>
              </td>
              <?php if(session("UserType") == "FO" && !$PickedUp): ?>
                <form action="<?= base_url("Orders/OrderSettingsChanged/" . $Order["Order_ID"]) ?>" method="post">
                <?= csrf_field() ?>
              <?php endif?>
              <td>
              <?php 
              $Timestring = $Order["PickupTime"];

              if (session("UserType") == 'C'){
                  if ($Timestring == null){
                    echo 'Pending...';
                  }
                  else{
                    $TimeFormat = date('m/d/Y h:i A', strtotime($Timestring));
                    echo $TimeFormat;
                  }
              }
              else if (session("UserType") == "FO" && !$PickedUp){
                echo '<input oninput="EnableSaveButton('. $index .')" type="datetime-local" ' . (($Timestring == null) ? '' : ('value="' . $Timestring . '"')) . ' class="form-control" id="PickUpTime" name="PickUpTime" min="';
                echo date("Y-m-d\TH:i");
                echo '">';
              }
              else{
                $TimeFormat = date('m/d/Y h:i A', strtotime($Timestring));
                echo $TimeFormat;
              }
              ?>   
              </td>
              <td>€ <?= $Order["TotalPrice"] ?></td>
              <td>
              <?php 
              
              if(session("UserType") == 'C'){
                echo $Order['FoodTruckName'];
              }
              else{
                echo $Order['User'];
              }
              ?>
              </td>
              <td>
              <?php


              $Status = $Order["Status"];

              //Echo's a message or button according to the order's Status and the type of user:
              if (session("UserType") == "C" && !$PickedUp){
                if($Status == 'Received'){
                  echo 'Order has been received';
                }
                else if ($Status == 'Processing'){
                  echo 'Order is being processed';
                }
                else if ($Status == 'Preparation'){
                  echo 'Order is being prepared';
                }
                else if($Status == 'Ready'){
                
                  echo '<a href="' . base_url("Orders/PickUpOrder/" . $Order['Order_ID']) . '" class="btn btn-primary bg-black border-black Searchfunctions">Pick up order</a>';
                }
              }
              else if (session("UserType") == "FO" && !$PickedUp){
                echo '<select oninput="EnableSaveButton('. $index . ')" name="Status" id="Status' . $index . '" class="form-select">';
                echo '<option ' . (($Status == 'Received') ? 'selected' : '') . '>Received</option>';
                echo '<option ' . (($Status == 'Processing') ? 'selected' : '') . '>Processing</option>';
                echo '<option ' . (($Status == 'Preparation') ? 'selected' : '') . '>Preparation</option>';
                echo '<option ' . (($Status == 'Ready') ? 'selected' : '') . '>Ready</option>';
                echo '</select>';                                 
              }
              else{
                echo '<i class="text-success fs-5 bi bi-check-circle-fill">Order complete</i>';
              }

              ?>
            </td>

            <?php if (session("UserType") == "FO" && !$PickedUp): ?>
              <td>
                <input value="Save" type="submit" id="SaveButton<?=$index?>" class="btn btn-primary rounded-pill btn-md bg-black border-black SearchFunctions" disabled>
              </td>
              </form>
            <?php endif ?>
            <?php if (session("UserType") == "FO" && $PickedUp): ?>
              <td>
              </td>
            <?php endif ?>
          </tr>
<?php endforeach ?>
        </tbody>
      </table>
    </div>
<?php else: ?>
    <div class="col-12 text-white text-center justify-content-center align-items-center d-flex" style="height:200px">
      <h3>Currently, you have no orders &#128546;</h3>
    </div>
<?php endif ?>

  </div>
</div>