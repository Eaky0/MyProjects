
SelectedUserType = "Consumer";

function ConvertForm(UserType){
    const Selected = document.getElementById(UserType);

    if (Selected !== SelectedUserType){

        if(UserType == 'Consumer'){
            const FoodTruckOwnerInput = document.getElementById("IfFoodTruckOwner");
            FoodTruckOwnerInput.innerHTML = "";
        }
        else{
            const FoodTruckOwnerInput = document.getElementById("IfFoodTruckOwner");            

            const FoodTruckNameColumn = document.createElement("div");
            FoodTruckNameColumn.classList.add("col-lg-2", "col-sm-12", "mt-2");

            const FTnameInput = document.createElement("input");
            FTnameInput.classList.add("form-control");
            FTnameInput.type = "text";
            FTnameInput.placeholder = "Food truck name"
            FTnameInput.name = "FTname";
            FTnameInput.id = "FTname";
            FTnameInput.required = true;


            const FoodTruckTelColumn = document.createElement("div");
            FoodTruckTelColumn.classList.add("col-lg-2", "col-sm-12", "mt-2");

            const TelInput = document.createElement("input");
            TelInput.classList.add("form-control");
            TelInput.type = "tel";
            TelInput.placeholder = "Phone Number"
            TelInput.name = "Tel";
            TelInput.id = "Tel";
            TelInput.required = true;


            FoodTruckNameColumn.appendChild(FTnameInput);
            FoodTruckTelColumn.appendChild(TelInput);

            FoodTruckOwnerInput.appendChild(FoodTruckNameColumn);
            FoodTruckOwnerInput.appendChild(FoodTruckTelColumn);
        }


        SelectedUserType = Selected;
    }
    
}


function CheckValidation(event){
    event.preventDefault();

    const AlertSection = document.getElementById('AlertSection');
    AlertSection.innerHTML = "";
    const AlertMessage = document.createElement('div');
    AlertMessage.classList.add("alert", "alert-danger");

    const AlertList = document.createElement('ul');

    const FoodTruckOwner = document.getElementById("FoodtruckOwner");

    //Get UserName, Email and Password values:
    const UserName = document.getElementById("UserName").value;
    const FirstName = document.getElementById("Fname").value;
    const LastName = document.getElementById("Lname").value;
    const BirthDate = document.getElementById("BirthDate").value;

    const Email = document.getElementById("Email").value;
    const Password = document.getElementById("Password").value;


    //Username validation:
    if (UserName.length < 10){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Username must consist of at least 10 letters";
        AlertList.appendChild(Problem);
    }

    //Check if Username is already in use
    fetch("http://localhost:8080/get-Users")
    .then(response => response.json())
    .then(Users => {

        const userExists = Users.some(User => User.NickName === UserName);

        if (userExists) {
            const Problem = document.createElement("li");
            Problem.innerHTML = "Username already in use";
            AlertList.appendChild(Problem);
        }
    });


    //First & Last name validation

    if (FirstName == ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "First name is required";
        AlertList.appendChild(Problem);
    }

    if (LastName == ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Surname is required";
        AlertList.appendChild(Problem);
    }


    //Date of birth validation
    if (BirthDate == ""){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Date of birth is required";
        AlertList.appendChild(Problem);
    }





    //Email-address validation
    const Emailexp = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/
    if(!Email.match(Emailexp)){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Invalid E-mail address";
        AlertList.appendChild(Problem);
    }

    //Password validation
    if(Password.length < 5){
        const Problem = document.createElement("li");
        Problem.innerHTML = "Password must consist of at least 5 letters";
        AlertList.appendChild(Problem);
    }

    //If it's a food truck owner, also make sure to validate the food truck name and phone number
    if(FoodTruckOwner.checked){
        const FTname = document.getElementById("FTname").value;
        const Phone = document.getElementById("Tel").value;

        //Food truck name validation
        if (FTname.length < 4){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Food truck name must consist of at least 4 letters";
            AlertList.appendChild(Problem);
        }

        //Check if Food Truck name/Phone number is already in use
        fetch("http://localhost:8080/get-FoodTrucks")
        .then(response => response.json())
        .then(FoodTrucks => {

            const FoodTruckExists = FoodTrucks.some(FoodTruck => FoodTruck.Name === FTname);

            if (FoodTruckExists) {
                const Problem = document.createElement("li");
                Problem.innerHTML = "Food truck name already in use";
                AlertList.appendChild(Problem);
            }

            const PhoneNumberInUse = FoodTrucks.some(FoodTruck =>  FoodTruck.Tel === Phone)

            if (PhoneNumberInUse) {
                const Problem = document.createElement("li");
                Problem.innerHTML = "Phone number already in use";
                AlertList.appendChild(Problem);
            }

        });

        //Phone number validation
        var phonePattern = /^(\+\d{1,3}\s?)?(\d{1,4}[\s-]?)?(\(\d{1,4}\)|\d{1,4})?[\s-]?\d{1,4}[\s-]?\d{1,4}$/;

        if (!Phone.match(phonePattern)){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Invalid phone number";
            AlertList.appendChild(Problem);
        }

    }




    if(AlertList.innerHTML !== ""){
        AlertMessage.appendChild(AlertList);
        AlertSection.appendChild(AlertMessage);
    }
    else{
        document.getElementById("SignUpForm").submit();
    }

}