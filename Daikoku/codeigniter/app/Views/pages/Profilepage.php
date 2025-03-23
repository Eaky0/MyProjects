
<div id="ProfileNameSection" class="container">
  <div class="row">
      <div class="col-lg-3 col-md-12 text-center">
        <img id="PfpSettings" src="<?= (session("ProfilePicture") === null)? base_url("staticimg/ProfilePic.jpg") : base_url("img/" . session("ProfilePicture"));?>" alt="Pfp">
        <button data-bs-toggle="modal" data-bs-target="#ChangePfp" class="btn btn-primary btn-lg bg-black border-black SearchFunctions">Change profile picture</button>
        <div class="modal fade" data-bs-backdrop="static" id="ChangePfp" tabindex="-1" aria-labelledby="ChangePfpLabel" aria-hidden="true">
            <div class="modal-dialog modal-dialog-centered">
                <div class="modal-content">
                    <div class="modal-header">                              
                    <h1 class="modal-title fs-5" id="ChangePfpLabel">Change profile picture</h1>
                    </div>
                    <div class="modal-body">          
                    <form action=<?= base_url('Profilepage/ProfilePictureChanged')?> method="post" id="PfpForm" enctype="multipart/form-data">
                    <?= csrf_field() ?>
                    <input type="file" id="Pfp" name="Pfp" class="form-control" accept="image/*">

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
                        <button id="CancelButton" type="button" class="btn btn-danger" data-bs-dismiss="modal">Cancel</button>
                        <button onclick="CheckFile(event)" class="btn btn-primary bg-black">Change</button>
                    </div>
                    </form>
                </div>
            </div>
        </div> <!--Modal ends here! --> 
      </div>
      <div class="col p-lg-5 mt-5 text-center">
          <h1 class="text-center display-1"><?php echo session('NickName');?></h1>
      </div>
  </div>
</div>


<div id="PersInfSection" class="container">
  <div class="row">
      <div class="col-12">
          <h1 class="text-white text-center">Personal Information</h1>
      </div>
      <form id="PfSettingsForm" action="<?=base_url('Profilepage/ProfileEdited');?>" method="post">
      <?= csrf_field() ?>
      <div class="col-12">
          <div class="form-floating SingleField">
              <input type="text" value="<?= session('NickName');?>"  class="form-control" id="pfname" name="NickName" disabled>
              <label for="pfname">Username</label>
          </div>
      </div>
      <div class="col-12 d-flex">
          <div class="form-floating DoubleField">
              <input type="text" value="<?= session('FirstName');?>"  class="form-control" id="Fname" name="Fname">
              <label for="Fname">First name</label>
          </div>
          <div class="form-floating DoubleField">
              <input type="text" value="<?= session('LastName');?>"  class="form-control" id="Lname" name="Lname">
              <label for="Lname">Last name</label>
          </div>
      </div>
      <div class="col-12">
          <div class="form-floating SingleField">
              <input id="Date" type="date" value="<?php echo session('BirthDate');?>" class="form-control" name="BirthDate">
              <label for="Date">Date of birth</label>
            </div>
      </div>
      <div class="col-12 d-flex">
          <div class="form-floating DoubleField">
              <input type="email" value="<?= session('Email');?>"  class="form-control" id="E-mail" name="Email" disabled>
              <label for="E-mail">E-mail</label>
          </div>
          <div class="form-floating DoubleField">
              <input type="password" value="<?= session('Password');?>" class="form-control" id="Password" name="Password">
              <label for="Password">Password</label>
          </div>
      </div>

      <div class="mt-2" id="AlertSection2">
                    <!--
                        <div class="alert alert-danger">
                            <ul>
                            </ul>
                        </div>
                    -->
        </div>
      
      
        <div class="col-12 text-center">
            <button id="Savebutton" onclick="CheckSettings(event)" class="btn btn-primary rounded-pill btn-lg bg-black border-black SearchFunctions">Save</button>
        </div>
      <form>
  </div>
</div>


<?php if(session("UserType") == "FO"): ?>
<div id="StatSection" class="container">
  <div class="row">
  <div class="col-12">
          <h1 class="text-center">Foodtruck statistics</h1>
  </div>
  </div>
  <div class="row">
      <div class="col-lg-6 col-sm-12 mt-2 bg-white rounded d-flex flex-column justify-content-center align-items-center">
            <label for="FTname">Name: </label>
            <h2 id="FTname"><?=$FoodTruck["Name"]?></h2>
            <label for="OrderAmount">Amount of orders received: </label>
            <h2 id="OrderAmount"><?=$OrderAmount ?></h2>
      </div>
      <div class="col-lg-6 col-sm-12 mt-2">
        <div class="bg-white rounded">
        <canvas id="TopProductChart" style="width:100%;max-width:600px"></canvas>
        </div>
      </div>   
  </div>
</div>

<script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.js"></script>

<?php 

$AmountArray = array();
$ProductArray = array();

foreach ($Top3Products as $Product){
    $ProductArray[] = $Product["ProductName"];
    $AmountArray[] = $Product["TotalAmount"];
}



?>

<script>

const AmountArray = <?= json_encode($AmountArray) ?>;
const ProductArray = <?= json_encode($ProductArray) ?>;
const barColors = ["red", "green","blue"]

new Chart("TopProductChart", {
  type: "pie",
  data: {
    labels: ProductArray,
    datasets: [{
      backgroundColor: barColors,
      data: AmountArray
    }]
  },
  options: {
    title: {
      display: true,
      text: "Top 3 best selling products",
  }
    
  }
});

</script>

<?php endif ?>




<script>
    const nFirstName = document.getElementById("Fname");
    const nLastName = document.getElementById("Lname");
    const nBirthDate = document.getElementById("Date");
    const nPassword = document.getElementById("Password");
    const Savebutton = document.getElementById("Savebutton");


    function enableSavebutton(){
        Savebutton.style.pointerEvents = 'auto';
        Savebutton.style.opacity = '1';
    }


    nFirstName.addEventListener('input', enableSavebutton);
    nLastName.addEventListener('input', enableSavebutton);
    nBirthDate.addEventListener('input', enableSavebutton);
    nPassword.addEventListener('input', enableSavebutton);
</script>

