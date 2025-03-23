<div id="HeaderSection" class="container">
  <div id="SectionText" class="row">
    <div class="col text-center">
      <h1 class="display-1">
        Review your order
      </h1>
    </div>
  </div>
</div>

<div id="OrderReviewSection" class="container">
    <h1 class="p-3">Order number: <?=$Order["Order_ID"]?></h1>
    <?php foreach($Order["Products"] as $index => $Product): ?>
    <div class="row p-3">
        <h4>What are your thoughts on <?=$Product["ProductName"]?>?</h4>
        <form id="ReviewForm<?=$index?>" method="post" action="<?= base_url('OrderReview/'. $Order["Order_ID"] . "/" . $Order["FoodTruckName"] . '/ReviewWritten'); ?>">
            <?= csrf_field() ?>
            <input type="hidden" name ="MenuName" value="<?=$Product["ProductName"]?>">
            <div class="col-lg-12 col-md-12 p-2">
                <textarea class="form-control" id="ReviewText<?=$index?>" placeholder="Lorem Ipsum..." rows="3" name="ReviewText"></textarea>
            </div>
            <div class="col-lg-12 col-md-12 p-2">
                <select class="form-select" id="Rating<?=$index?>" name="Rating">
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

            <div id="AlertSection<?=$index?>" class="col-lg-4 col-md-12 p-2">
            <!--    
                <div class="alert alert-danger">
                  <ul>
                    <li>not good</li>
                  </ul>
                </div>
            -->
            </div>


            <div class="col-lg-3 col-sm-12 p-2">
                <button class="form-control btn btn-primary btn-lg bg-black text-white border-black SearchFunctions" onclick="CheckReview(<?=$index?>, event)" >Send review</button>
            </div>
        </form>
    </div>
    <?php endforeach?>

</div>