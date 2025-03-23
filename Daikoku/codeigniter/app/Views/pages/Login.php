<div class="container-fluid FormTab">


  <div class="row">
    <div class="col-12">
      <h1>Login</h1>
    </div>
  </div>
  <form id="LoginForm" action=<?= base_url('Login') ?> method="post">
  <?= csrf_field() ?>
  <div class="row justify-content-center" id ="ProfileType">
    <div class="col-lg-1 col-sm-4">
      <input id="Consumer" type="radio" name="C-FO" value="C" required checked><h6>Consumer</h6>         
    </div>
    <div class="col-lg-1 col-sm-4">
      <input id="FoodTruckOwner" type="radio" name="C-FO" value="FO" required><h6>Food truck owner</h6>
    </div>
  </div>
  
  <div class="row justify-content-center">
    <div class="col-lg-2 col-sm-12 mt-2">
      <input type="text" class="form-control" placeholder="E-mail address" id="Email" name='Email'>
    </div>
  </div>

  <br>
  <div class="row justify-content-center">
    <div class="col-lg-2 col-sm-12 mt-2">
      <input type="password" class="form-control" placeholder="Password" id="Password" name='Password'>
    </div>
  </div>

  <div class="row" id="DecisionMaking">
    <div class="col">
      <button onclick="CheckUserValidation(event)" class="btn btn-lg rounded-pill btn-primary bg-black border-warning m-3 SearchFunctions">Login</button>
    </div>
  </div>
  </form>

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


  <div class="row">
    <div class="col-lg-12 col-sm-12 mt-2">
      <h6>Don't have an account yet?,<a href="SignUp">sign up </a>now!</h6>
    </div>
</div>
<br>
</div>
