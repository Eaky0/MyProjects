<div id="HeaderSection" class="container">
  <div id="SectionText" class="row">
    <div class="col text-center">
      <h1 class="display-1">Contact</h1>
    </div>
  </div>
</div>

<div id="ContactSection" class="container">
  <div id="ContactHeaderText" class="row">
    <div class="col text-center text-white">
      <h2>How can we help you?</h2>
      <p>For questions or needs, you can get in touch with us directly through various sources!</p>
    </div>
  </div>

  <div id="ContactSourceSection" class="row">
    <div class="text-white col-lg-6 col-sm-12 d-flex">
      <i id="PhoneIcon" class="bi bi-telephone-fill"></i>
      <h4 class="text-center">+31 6 87442993</h4>
    </div>
    <div class="text-white col-lg-6 col-sm-12 d-flex">
      <h5 class="text-center">Available from 09:00 to 18:00</h5>
    </div>
    <div  class="text-white col-12 d-flex">
      <i id="LocationIcon" class="bi bi-geo-alt-fill"></i>
      <h4 class="text-center">Agoralaan gebouw D, 3590 Diepenbeek Belgium</h4>
    </div>
  </div>
</div>

<div id="MessagingSection" class="container">
  <div class="row">
    <div class="col text-center text-white">
      <p>While unavailable, you can also send us a message!</p>
    </div>
    <div class="col-12">
      <form id="ContactForm" action=<?= base_url("Contactpage/MessageSent")?> method="post">
      <?= csrf_field() ?>
        <div class="input-group mb-3">
          <span class="input-group-text bg-dark border-dark" id="basic-addon1"><i id="EnvelopeIcon" class="bi bi-envelope-fill"></i></span>
          <input type="email" class="form-control" id="Email" name="Email" id="exampleFormControlInput1" placeholder="name@example.com">
        </div>
        <div class="mb-3">
          <textarea class="form-control" id="MsgText" name="MsgText" id="exampleFormControlTextarea1" placeholder="Lorem Ipsum..." rows="3"></textarea>
        </div>

        <div class="mt-2" id="AlertSection">
          <!--
          <div class="alert alert-danger">
            <ul>
            </ul>
          </div>
          -->
        </div>

        <div class="text-center mb-4">
          <button class="btn btn-primary rounded-pill btn-lg bg-black border-black SearchFunctions" onclick="CheckValidation(event)">Message</button>
        </div>
      </form>
    </div>
  </div>
</div>