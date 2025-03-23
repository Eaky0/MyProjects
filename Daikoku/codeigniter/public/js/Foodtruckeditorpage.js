
  //After clicking on cancel in a modal with a form for editing menu's, form input values will be reset to empty.
  const CancelButton1 = document.getElementById("CancelButton1");
  const CancelButton2 = document.getElementById("CancelButton2");
  const CancelButton3 = document.getElementById("CancelButton3");
  const CancelButton4 = document.getElementById("CancelButton4");


  function Resetform1(){
      document.getElementById("CategoryForm").reset();
      const AlertSection = document.getElementById('AlertSection4');
      AlertSection.innerHTML = "";
  }

  function Resetform2(){
      document.getElementById("ProductForm").reset();
      const AlertSection = document.getElementById('AlertSection5');
      AlertSection.innerHTML = "";
  }

  function Resetform3(){
      document.getElementById("IVForm").reset();
      const AlertSection = document.getElementById('AlertSection6');
      AlertSection.innerHTML = "";
  }

  function Resetform4(){
     document.getElementById("MainImagesForm").reset();
     const AlertSection = document.getElementById('AlertSection');
     AlertSection.innerHTML = "";
  }

  function Resetform5(MenuAmount){

    for (index = 0; index < MenuAmount; ++index){
        document.getElementById("EditProductForm" + (index + 1)).reset();
        const AlertSection = document.getElementById('AlertSection' + (6 + index + 1));
        AlertSection.innerHTML = "";
    }
  }

  CancelButton1.addEventListener('click', Resetform1);
  CancelButton2.addEventListener('click', Resetform2);
  CancelButton3.addEventListener('click', Resetform3);
  CancelButton4.addEventListener('click', Resetform4);


//Editing menu's, the main section or the contact info section, triggers their corresponding save buttons:
  function EnableSaveButton(ButtonId){
      const SaveButton = document.getElementById(ButtonId);
      SaveButton.style.pointerEvents = 'auto';
      SaveButton.style.opacity = '1';
  }



function mainMediaValidation(event){
    event.preventDefault();

    const MediaInput = document.getElementById("MainI");
    const Image = MediaInput.files[0];

    const AlertSection = document.getElementById('AlertSection');
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');

    if (!Image){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Please select some images";
        AlertList.appendChild(Problem);
    }
    else{
        const ImageFiles = Array.from(MediaInput.files);

        const InvalidImageExists = ImageFiles.some(Image => {
            const ImageBytes = Image.size;
            const MBLimit = 20;
            const ByteLimit = MBLimit * (1024**2);
            
            return ImageBytes > ByteLimit;
        });



        if (InvalidImageExists){
            const Problem = document.createElement("li");
            Problem.innerHTML = "You've added images that are too large (Limit per image = 20 MB)";
            AlertList.appendChild(Problem);
        }
    }

    if(AlertList.innerHTML !== ""){
        AlertMessage.appendChild(AlertList);
        AlertSection.appendChild(AlertMessage);
    }
    else{
        document.getElementById("MainImagesForm").submit();
    }
}


function MainSectionValidation(event){
    event.preventDefault();

    const AlertSection = document.getElementById('AlertSection2');
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');

    const PublishCheck = document.getElementById("Publish");

    if (PublishCheck.checked == true){
        const DescHeader = document.getElementById("DescHeader").value;
        const DescBody = document.getElementById("DescBody").value;
        const Country = document.getElementById("Country").value;
        const Kitchen = document.getElementById("KitchenType").value;
        const Vehicle = document.getElementById("VehicleType").value;

        if (DescHeader === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Your Description header is empty";
            AlertList.appendChild(Problem);
        }

        if (DescBody === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Your Description body is empty";
            AlertList.appendChild(Problem);
        }

        if (Country === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "The country in which this food truck resides is not given";
            AlertList.appendChild(Problem);
        }

        if (Kitchen === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "The kitchen type of this food truck is not given";
            AlertList.appendChild(Problem);
        }

        if (Vehicle === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "The food truck's vehicle type is not given";
            AlertList.appendChild(Problem);
        }
    }

    if(AlertList.innerHTML !== ""){
        AlertMessage.appendChild(AlertList);
        AlertSection.appendChild(AlertMessage);
    }
    else{
        document.getElementById("MainSectionForm").submit();
    }
}


function ContactSectionValidation(event, ThisFoodTruck){
    event.preventDefault();

    const AlertSection = document.getElementById('AlertSection3');
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');


    const PhoneNumber = document.getElementById("PhoneNumber").value;
    const OpeningTime = document.getElementById("OpeningTime").value;
    const ClosingTime = document.getElementById("ClosingTime").value;
    const NextLocation = document.getElementById("NextLocation").value;
    const CurrentLocation = document.getElementById("CurrentLocation").value;

    if (PhoneNumber === ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "A telephone number is not given";
        AlertList.appendChild(Problem);
    }

    //Check if Food Truck name/Phone number is already in use
    fetch("http://localhost:8080/get-FoodTrucks")
    .then(response => response.json())
    .then(FoodTrucks => {
        const PhoneNumberInUse = FoodTrucks.some(FoodTruck => {
            return FoodTruck.Tel === PhoneNumber && FoodTruck.Name !== ThisFoodTruck})

        if (PhoneNumberInUse) {
            const Problem = document.createElement("li");
            Problem.innerHTML = "Phone number already in use";
            AlertList.appendChild(Problem);
        }

    });



    if (OpeningTime === ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "An opening time is not given";
        AlertList.appendChild(Problem);
    }

    if (ClosingTime === ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "A closing time is not given";
        AlertList.appendChild(Problem);
    }

    if (CurrentLocation === ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "A current location is not given";
        AlertList.appendChild(Problem);
    }

    if (NextLocation === ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "A future location is not given";
        AlertList.appendChild(Problem);
    }

    if(AlertList.innerHTML !== ""){
        AlertMessage.appendChild(AlertList);
        AlertSection.appendChild(AlertMessage);
    }
    else{
        document.getElementById("ContactSectionForm").submit();
    }

}


function AddingCategoryValidation(event){
    event.preventDefault();

    const AlertSection = document.getElementById('AlertSection4');
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');

    Category = document.getElementById("NewCategory").value;

    const expression = /^[a-zA-Z\-]+$/;

    if (!Category.match(expression)){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Invalid category name, you can only use letters and hyphens ('-')";
        AlertList.appendChild(Problem);
    }

    if(AlertList.innerHTML !== ""){
        AlertMessage.appendChild(AlertList);
        AlertSection.appendChild(AlertMessage);
    }
    else{
        document.getElementById("CategoryForm").submit();
    }


}

function CheckNewProductValidation(event){
    event.preventDefault();

    const AlertSection = document.getElementById('AlertSection5');
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');

    const ProductName = document.getElementById("NewProductName").value;
    const ProductPrice = document.getElementById("NewProductPrice").value;
    const ProductDescription = document.getElementById("NewProductDescription").value;    
    const ProductIngredients = document.getElementById("NewProductIngredients").value;
    const ProductAllergenes = document.getElementById("NewProductAllergenes").value;

    //Fetch menu data van foodtruck:
    fetch("http://localhost:8080/get-menus")
    .then(response => response.json())
    .then(Menus => {

        const expression = /^[a-zA-Z \-]+$/;

        if (!ProductName.match(expression)){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Invalid product name, you can only use letters and hyphens ('-')";
            AlertList.appendChild(Problem);
        }

        const ProductNameExists = Menus.some(Product => {
            return ProductName == Product.Name});

        if (ProductNameExists) {
            const Problem = document.createElement("li");
            Problem.innerHTML = "There is already a menu with this name";
            AlertList.appendChild(Problem);
        }


        if (ProductPrice === "" || ProductPrice == 0){
            const Problem = document.createElement("li");
            Problem.innerHTML = "We suppose you want to earn money right? (No price given)";
            AlertList.appendChild(Problem);
        }

        if (ProductDescription === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Customers are always curious about what you're bringing to the table! (No description included)";
            AlertList.appendChild(Problem);
        }
    
        if (ProductIngredients === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "A consumer should know what they're eating (No ingredients included)";
            AlertList.appendChild(Problem);
        }
    
        if (ProductAllergenes === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "It would be a good idea to warn your clients about possible allergenes";
            AlertList.appendChild(Problem);
        }
    
        const MenuMediaInput = document.getElementById("NewProductIV");
        const IV = MenuMediaInput.files[0];
    
        if (IV){
            const IVFiles = Array.from(MenuMediaInput.files);
    
            const InvalidIVExists = IVFiles.some(IV => {
                const IVBytes = IV.size;
                const MBLimit = 50;
                const ByteLimit = MBLimit * (1024**2);
    
                return IVBytes > ByteLimit;
            });
    
            if (InvalidIVExists){
                const Problem = document.createElement("li");
                Problem.innerHTML = "You've added images or videos that are too large (Limit per image/video = 50 MB)";
                AlertList.appendChild(Problem);
            }
        }
    
        if(AlertList.innerHTML !== ""){
            AlertMessage.appendChild(AlertList);
            AlertSection.appendChild(AlertMessage);
        }
        else{
            document.getElementById("ProductForm").submit();
        }

    });
    
}

function MenuMediaValidation(event){
    event.preventDefault();

    const MenuMediaInput = document.getElementById("ProductIV");
    const IV = MenuMediaInput.files[0];

    const AlertSection = document.getElementById('AlertSection6');
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');

    if (!IV){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Please select some images or videos";
        AlertList.appendChild(Problem);
    }
    else{
        const IVFiles = Array.from(MenuMediaInput.files);

        const InvalidIVExists = IVFiles.some(IV => {
            const IVBytes = IV.size;
            const MBLimit = 50;
            const ByteLimit = MBLimit * (1024**2);

            return IVBytes > ByteLimit;
        });

        if (InvalidIVExists){
            const Problem = document.createElement("li");
            Problem.innerHTML = "You've added images or videos that are too large (Limit per image/video = 50 MB)";
            AlertList.appendChild(Problem);
        }
    }

    if(AlertList.innerHTML !== ""){
        AlertMessage.appendChild(AlertList);
        AlertSection.appendChild(AlertMessage);
    }
    else{
        document.getElementById("IVForm").submit();
    }
}


function EditProductValidation(event, Product, OldName){
    event.preventDefault();

    const AlertSection = document.getElementById('AlertSection' + (6 + Product));
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');

    const ProductName = document.getElementById("ProductName"+Product).value;
    const ProductPrice = document.getElementById("ProductPrice"+Product).value;
    const ProductDescription = document.getElementById("ProductDescription"+Product).value;    
    const ProductIngredients = document.getElementById("ProductIngredients"+Product).value;
    const ProductAllergenes = document.getElementById("ProductAllergenes"+Product).value;


    //Fetch menu data van foodtruck:
    fetch("http://localhost:8080/get-menus")
    .then(response => response.json())
    .then(Menus => {

        const expression = /^[a-zA-Z \-]+$/;

        if (!ProductName.match(expression)){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Invalid product name, you can only use letters and hyphens ('-')";
            AlertList.appendChild(Problem);
        }

        const ProductNameExists = Menus.some(Product => {
            return ProductName == Product.Name && ProductName != OldName});

        if (ProductNameExists) {
            const Problem = document.createElement("li");
            Problem.innerHTML = "There is already a menu with this name";
            AlertList.appendChild(Problem);
        }

        if (ProductPrice === "" || ProductPrice == 0){
            const Problem = document.createElement("li");
            Problem.innerHTML = "We suppose you want to earn money right? (No price given)";
            AlertList.appendChild(Problem);
        }

        if (ProductDescription === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Customers are always curious about what you're bringing to the table! (No description included)";
            AlertList.appendChild(Problem);
        }
    
        if (ProductIngredients === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "A consumer should know what they're eating (No ingredients included)";
            AlertList.appendChild(Problem);
        }
    
        if (ProductAllergenes === ""){
            const Problem = document.createElement("li");
            Problem.innerHTML = "It would be a good idea to warn your clients about possible allergenes";
            AlertList.appendChild(Problem);
        }
    
        if(AlertList.innerHTML !== ""){
            AlertMessage.appendChild(AlertList);
            AlertSection.appendChild(AlertMessage);
        }
        else{
            document.getElementById("EditProductForm"+Product).submit();
        }

    });




}

