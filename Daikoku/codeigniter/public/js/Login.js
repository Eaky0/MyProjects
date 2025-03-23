function CheckUserValidation(event){
    event.preventDefault();

    

    //User validation:
    fetch("http://localhost:8080/get-Users")
    .then(response => response.json())
    .then(Users => {

        const AlertSection = document.getElementById('AlertSection');
        AlertSection.innerHTML = "";
        const AlertMessage = document.createElement('div');
        AlertMessage.classList.add("alert", "alert-danger");

        const AlertList = document.createElement('ul');

        const ConsumerRadio = document.getElementById("Consumer");
        const FoodTruckOwnerRadio = document.getElementById("FoodTruckOwner");

        const Email = document.getElementById("Email").value;
        const Password = document.getElementById("Password").value;

        //Email-address validation
        const Emailexp = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/

        ValidEmail = false;
        if(!Email.match(Emailexp)){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Invalid E-mail address";
            AlertList.appendChild(Problem);
            }
        else{
            ValidEmail = true;
        }
        
        //Password validation
        ValidPassword = false;
        if(Password.length < 5){
            const Problem = document.createElement("li");
            Problem.innerHTML = "Password must consist of at least 5 letters";
            AlertList.appendChild(Problem);
        }
        else{
            ValidPassword = true;
        }

        const ConsumerExists = Users.some(User => 
            { return (User.Email === Email && User.Password === Password 
                && User.UserType === 'C');});

        const FoodTruckerExists = Users.some(User => 
            { return (User.Email === Email && User.Password === Password 
                && User.UserType === 'FO');});        
        
        if(!ConsumerExists && ConsumerRadio.checked == true){
            const Problem = document.createElement("li");
            Problem.innerHTML = "A consumer with this email and password does not exist";
            AlertList.appendChild(Problem);
            AlertMessage.appendChild(AlertList);
            AlertSection.appendChild(AlertMessage);
        }
        else if (!FoodTruckerExists && FoodTruckOwnerRadio.checked == true){
            const Problem = document.createElement("li");
            Problem.innerHTML = "A foodtrucker with this email and password does not exist";
            AlertList.appendChild(Problem);
            AlertMessage.appendChild(AlertList);
            AlertSection.appendChild(AlertMessage);
        }
        else{
            document.getElementById("LoginForm").submit();
        }
    })
    .catch(error => {
        console.error('Error fetching user data:', error);
    });
}

