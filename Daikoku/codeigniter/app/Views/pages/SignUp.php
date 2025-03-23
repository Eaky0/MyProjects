<div class="container-fluid FormTab">
      <div class="row">
        <div class="col-12">
          <h1>Sign up</h1>
        </div>
      </div>
      <form id="SignUpForm" action="<?=base_url("SignUp/SignedUp") ?>" method="post">
      <?= csrf_field() ?>
      <div class="row justify-content-center" id ="ProfileType">
        <div class="col-lg-2 col-sm-12">
          <input id="Consumer" type="radio" name="C-FO" value="C" onclick="ConvertForm('Consumer')" checked>
          <h6>Consumer</h6>         
        </div>
        <div class="col-lg-2 col-sm-12">
          <input id="FoodtruckOwner" type="radio" name="C-FO" value="FO" onclick="ConvertForm('FoodtruckOwner')"><h6>Food truck owner</h6>
        </div>
      </div>

      <div class="row justify-content-center">
        <div class="col-lg-4 col-sm-12">
          <input class="form-control" type="text" id="UserName" name="UserName" placeholder="Username" required>
        </div>
      </div>

      <div class="row justify-content-center">
        <div class="col-lg-2 col-sm-12 mt-2">
          <input type="text" class="form-control" id="Fname" name="Fname" placeholder="First name" required>
        </div>
        <div class="col-lg-2 col-sm-12 mt-2">
          <input type="text" class="form-control" id="Lname" name="Lname" placeholder="Surname" required>
        </div>
      </div>

      <div class="row justify-content-center">
        <div class="col-lg-4 col-sm-12 mt-2">
          <label for="BirthDate">Date of birth</label>
          <input  class="form-control" id="BirthDate" name="BirthDate" type="date" required>
        </div>
      </div>

      <div class="row justify-content-center">
        <div class="col-lg-2 col-sm-12 mt-2">
          <input type="text" class="form-control" id="Email" name="Email" placeholder="E-mail address" required>
        </div>
        <div class="col-lg-2 col-sm-12 mt-2">
          <input type="password" class="form-control" id="Password" name="Password" placeholder="password" required>
        </div>
      </div>


      <div class="row justify-content-center" id="IfFoodTruckOwner">
        <!--
        <div class="col-lg-3 col-sm-12 mt-2">
          <input type="text" class="form-control" id="FTname" name="FTname" placeholder="Food truck name" required>
        </div>
        <div class="col-lg-3 col-sm-12 mt-2">
          <input type="tel" class="form-control" id="Tel" name="Tel" placeholder="Phone number" required>
        </div>
      -->
      </div>

      <div class="row justify-content-center">
        <div class="col-lg-3 col-sm-12 mt-2" id="AlertSection">
          <!--
          <div class="alert alert-danger">
            <ul>
            </ul>
          </div>
          -->
        </div>
      </div>
        

      <div class="row" id="DecisionMaking">
        <div class="col">
          <button onclick="CheckValidation(event)" class="btn btn-lg rounded-pill btn-primary bg-black border-warning m-3 SearchFunctions">Sign up</button>
        </div>
      </div>  
    </form>
  </div>
