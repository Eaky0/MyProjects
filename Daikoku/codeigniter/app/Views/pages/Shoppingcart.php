<div id="HeaderSection" class="container">
  <div id="SectionText" class="row">
    <div class="col text-center">
      <h1 class="display-1">Shopping Cart</h1>
    </div>
  </div>
</div>

<div id="CartSection" class="container">
  <div class="row">
<?php if(!empty($ShoppingCartProducts)): ?>
    <div class="col-12 text-white">
      <h1>Products</h1>
    </div>
    <div class="table-responsive col-12">
      <table class="table">
        <thead>
          <tr>
            <th scope="col">#</th>
            <th scope="col">Product</th>
            <th scope="col">Price</th>
            <th scope="col">Amount</th>
            <th scope="col">FoodTruck</th>
            <th scope="col"></th>
          </tr>
        </thead>
        <tbody>
          <?php 
          foreach($ShoppingCartProducts as $index => $Product):?>
          <tr>
            <th scope="row"><?= $index + 1 ?></th>
            <td><?= $Product["ProductName"]?></td>
            <td>€ <?= $Product["ProductPrice"]?></td>
            <td>
            <form id="AmountForm<?= $index + 1 ?>" action="<?= base_url("Shoppingcart/ChangedAmount")?>" method="post">
            <?= csrf_field() ?>
              <input type="hidden" name="ProductName" value="<?= $Product["ProductName"]?>">
              <input type="hidden" name="FoodTruckName" value="<?= $Product["FoodTruckName"]?>">
              <input min="1" value="<?= $Product["Amount"]?>" type="number" name="ProductAmount" style="max-width: 50px;" autocomplete="off" onkeydown="return false"  oninput="ChangeAmount(<?= $index + 1?>)">
            </form>
            </td>
            <td><?= $Product["FoodTruckName"]?></td>
            <td>
              <form action="<?= base_url("Shoppingcart/DeletedFromCart")?>" method="post">
              <?= csrf_field() ?>
                <input type="hidden" name="ProductName" value="<?= $Product["ProductName"]?>">
                <input type="hidden" name="FoodTruckName" value="<?= $Product["FoodTruckName"]?>">
                <button type="submit" class="btn bg-black DeleteProductIcon"><i class="bi bi-dash-square"></i></button>
              </form>
            </td>
          </tr>
          <?php endforeach ?>
        </tbody>
        <tfoot>
          <tr>
          <th scope="row">Total Price</th>
          <td>€ <?= $totalprice ?></td>
          </tr>
        </tfoot>
      </table>
    </div>

    <div class="col-4 mx-auto" id="AlertSection">
      <!-- 
      <div class="alert alert-danger text-center">
        To order, you need to place products of only 1 foodtruck in your shopping cart!
      </div>
      -->
    </div>

<?php
  $serializedCart = json_encode($ShoppingCartProducts);
?>


    <div class="col-12">
      <form id="ConfirmationForm" action="<?= base_url("ShoppingCart/ConfirmOrder")?>" method="post">
      <?= csrf_field() ?>
      <input type="hidden" id="Products" name="Products" value="<?= htmlspecialchars($serializedCart)?>">
      <input type="hidden" name="TotalPrice" value=<?= $totalprice ?>>
      <button onclick="CheckFoodTruck(event)" class="btn bg-black mt-2" id="ActionButton">Confirm order</button>
      </form>
    </div>
<?php else: ?>
  <div class="col-12 text-white text-center justify-content-center align-items-center d-flex" style="height:200px">
    <h3>Your shopping cart is empty &#128546;</h3>
  </div>
<?php endif ?>
  </div>
</div>