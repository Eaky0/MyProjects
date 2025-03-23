<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Food Truck Editor</title>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.5.0/font/bootstrap-icons.css">
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.bundle.min.js"
    integrity="sha384-MrcW6ZMFYlzcLA8Nl+NtUVF0sA7MsXsP1UyJoMp4YLEuNSfAP+JcXn/tWtIaxVXM"
    crossorigin="anonymous" defer></script>
    <script src=<?= base_url("js/Foodtruckeditorpage.js") ?> defer></script>
    <link href="<?= base_url("css/Optiontab.css") ?>" rel="stylesheet">
    <link href="<?= base_url("css/Foodtruckinfopage.css") ?>" rel="stylesheet"> 
    <link href="<?= base_url("css/Foodtruckeditorpage.css") ?>" rel="stylesheet"> 

  </head>
  <body>
    <nav class="navbar navbar-expand-lg bg-dark">
      <div class="container-fluid">
        <img src="staticimg/Daikokulogobgremoved.png" alt="logo" width="200" height="90">
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#DaikokuToggler" aria-controls="DaikokuToggler" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-dark navbar-toggler-icon"></span>
        </button>
    
        <div class="collapse navbar-collapse" id="DaikokuToggler">
          <ul class="navbar-nav nav-underline me-auto mb-2 mb-lg-0" id="Optionanchor">
            <li class="nav-item">
              <a class="nav-link" href="<?= base_url("Mainpage")?>"><h2>Cancel</h2></a>
            </li>
          </ul>
  
          <ul class="navbar-nav" id="ProfileOptionanchor">
            <li class="nav-item">
              <div class="dropdown">
              <a class="nav-link dropdown-toggle text-white" role="button" data-bs-toggle="dropdown" aria-expanded="false"><img id="NavPfpSettings" src="<?= (session("ProfilePicture") === null)? base_url("staticimg/ProfilePic.jpg") : base_url("img/" . session("ProfilePicture"));?>" alt="Pfp"></a>
              <ul class="dropdown-menu dropdown-menu-end bg-black nav-underline">
                <li><a class="dropdown-item" href="Profilepage">Profile</a></li>
                <!--If the user is a food truck owner, this seimg/ProfilePic.jpgtting wil appear for them-->
                <li><a class="dropdown-item" href=<?= base_url("Orders")?>>Orders</a></li>
                <li><a class="dropdown-item" href=<?= base_url("Chatpage")?>>Chats</a></li>
                <li><a class="dropdown-item" href="<?= base_url("Foodtruckeditorpage") ?>">Food Truck Editor</a></li>
                <li><a class="dropdown-item" href="<?= base_url("Logout") ?>">Log Out</a></li>
              </ul>
            </div>
            <li>
          </ul>
        </div>
        </div>
    </nav>
