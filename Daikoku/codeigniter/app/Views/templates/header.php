<!DOCTYPE html>
<html lang="en">
<head>
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.11.2/font/bootstrap-icons.min.css">
    <link rel="stylesheet" type="text/css" href=<?= base_url("css/Optiontab.css") ?>>    
    <link rel="stylesheet" type="text/css" href=<?= base_url("css/" . esc($title) . ".css") ?>>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-C6RzsynM9kWDrMNeT87bh95OGNyZPhcTNXj1NW7RuBCsyN/o0jlpcV8Qyq46cDfL" crossorigin="anonymous" defer></script>
    <script src=<?= base_url("js/" . esc($title) . ".js") ?> defer></script>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?= esc($title) ?></title>
</head>
<body>
<nav class="navbar navbar-expand-lg bg-dark">
    <div class="container-fluid">
      <a class="navbar-brand" href="<?=base_url("Mainpage")?>">
        <img src="<?=base_url("staticimg/Daikokulogobgremoved.png")?>" alt="logo" width="200" height="90">
      </a>

      <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#DaikokuToggler" aria-controls="DaikokuToggler" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-dark navbar-toggler-icon"></span>
      </button>
  
      <div class="collapse navbar-collapse" id="DaikokuToggler">
        <ul class="navbar-nav nav-underline me-auto mb-2 mb-lg-0" id="Optionanchor">
          
        <?php if (session('LoggedIn') == true && session('UserType') == 'C'): ?>
          <li class="nav-item">
            <a class="nav-link" href=<?= base_url("Foodtruckspage")?>><h2>Food trucks</h2></a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href=<?= base_url("Eventspage")?>><h2>Events</h2></a>
          </li>
        <?php endif ?>
          <li class="nav-item">
            <a class="nav-link" href=<?= base_url("FAQpage")?>><h2>FAQ</h2></a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href=<?= base_url("Contactpage")?>><h2>Contact</h2></a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href=<?= base_url("Accessibility")?>><h2>Accessibility</h2></a>
          </li>
        <?php if (session('LoggedIn') == false): ?>
          <li class="nav-item">
            <a class="nav-link" href="<?= base_url("Login")?>"><h2>Login</h2></a>
          <li>
          <li class="nav-item">
            <a class="nav-link" href="<?= base_url("SignUp")?>"><h2>Sign up</h2></a>
          <li>
        </ul>
      <?php else: ?> 

        </ul>
        <ul class="navbar-nav" id="ProfileOptionanchor">
          <li class="nav-item">
            <div class="dropdown">
              <a class="nav-link dropdown-toggle text-white" role="button" data-bs-toggle="dropdown" aria-expanded="false"><img id="NavPfpSettings" src="<?= (session("ProfilePicture") === null)? base_url("staticimg/ProfilePic.jpg") : base_url("img/" . session("ProfilePicture"));?>" alt="Pfp"></a>
            <ul class="dropdown-menu dropdown-menu-end bg-black nav-underline">
              <li><a class="dropdown-item" href=<?= base_url("Profilepage")?>>Profile</a></li>
              <?php if (session('UserType') == 'C'): ?>
              <li><a class="dropdown-item" href=<?= base_url("Shoppingcart")?>>Shopping cart</a></li>
              <?php endif?>
              <li><a class="dropdown-item" href=<?= base_url("Orders")?>>Orders</a></li>
              <li><a class="dropdown-item" href=<?= base_url("Chatpage")?>>Chats</a></li>
              <!--If the user is a food truck owner, this setting wil appear for them-->
              <?php if (session('UserType') == 'FO'): ?>
              <li><a class="dropdown-item" href=<?= base_url("Foodtruckeditorpage")?>>Food truck editor</a></li>

              <?php endif ?>
              <li><a class="dropdown-item" href="<?= base_url("Logout")?>">Logout</a></li>
            </ul>
            </div>
          </li>
        </ul>

    <?php endif ?>
      </div>
    </div> 
  </nav>
