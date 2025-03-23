const Range = document.getElementById("Price-Range");
const DefaultRangeValue = Range.value;
const RangeInput = document.getElementById("Range-Value");

Range.addEventListener('input', function() {
    RangeInput.textContent = "€ " + Range.value + ".00";
});

document.addEventListener('DOMContentLoaded', function(){

    fetch("http://localhost:8080/load-food-trucks")
    .then(response => response.json())
    .then(data => {
        const CardSet = document.getElementById('FoodTruckSection');

        CardSet.innerHTML = "";

        data.forEach(FoodTruck => {
            const Column = document.createElement('div')
            Column.classList.add('col-lg-3', 'col-md-6', 'col-sm-6', 'd-flex',
            'justify-content-center');

            const Card = document.createElement('div');
            Card.classList.add('card', 'shadow', 'FoodTruckCard');
            
            const CardBody = document.createElement('div');
            CardBody.classList.add('card-body');

        


            const MainImage = document.createElement('img');

            if (FoodTruck.Media != null){
                MainImage.setAttribute('src', "img/" + FoodTruck.Media);
            }
            else{
                MainImage.setAttribute('src', "staticimg/FoodtruckStaticIcon.png");

            }

            MainImage.classList.add('img-fluid', 'card-img-top');
            MainImage.setAttribute('Alt', 'Food truck Photo');

            const CardTitle = document.createElement('h5');
            CardTitle.classList.add('card-title');
            CardTitle.innerHTML = FoodTruck.Name;

            const CardText = document.createElement('p');
            CardText.classList.add('text-truncate');
            CardText.innerHTML = FoodTruck.Description;

            const Checkbutton = document.createElement('a');
            Checkbutton.setAttribute('href', "Foodtruckinfopage/" + FoodTruck.Name);
            Checkbutton.classList.add('btn','btn-primary', 'text-black', 'bg-white', 'border-black');
            Checkbutton.innerHTML = 'Check it out!'

            CardBody.appendChild(CardTitle);
            CardBody.appendChild(CardText);
            CardBody.appendChild(Checkbutton);

            Card.appendChild(MainImage);
            Card.appendChild(CardBody);
            Column.appendChild(Card);
            CardSet.appendChild(Column);

        });
    })
    .catch(error => {
        console.error('Error:', error);
    })

});

function FetchFilter(){

    const Searchbar = document.getElementById('SearchBar').value;

    const CountryForm = document.getElementById('panel-collapseCountry');
    const Countries = CountryForm.querySelectorAll('input');

    const CountryData = {}

    Countries.forEach(Country =>{
        if (Country.checked){
            CountryData[Country.id] = true;
        }

    })


    const KitchenForm = document.getElementById('panel-collapseKitchen');
    const Kitchens = KitchenForm.querySelectorAll('input');

    const KitchenData = {}

    Kitchens.forEach(Kitchen =>{
        if (Kitchen.checked){
            KitchenData[Kitchen.id] = true;
        }

    })

    const VehicleForm = document.getElementById('panel-collapseVehicle');
    const Vehicles = VehicleForm.querySelectorAll('input');

    const VehicleData = {}

    Vehicles.forEach(Vehicle =>{
        if (Vehicle.checked){
            VehicleData[Vehicle.id] = true;
        }
 
    })

    const PriceRange = document.getElementById('Price-Range');
    const range = PriceRange.value;

    const FilterData = {}

    FilterData['CountryFilter'] = CountryData;
    FilterData['KitchenFilter'] = KitchenData;
    FilterData['VehicleFilter'] = VehicleData;
    FilterData['SearchBar'] = Searchbar;
    FilterData.range = range;

    fetchResults(FilterData);

}

function fetchSearch(){
    const Searchbar = document.getElementById('SearchBar').value;
    const CountryForm = document.getElementById('panel-collapseCountry');
    const Countries = CountryForm.querySelectorAll('input');

    const CountryData = {}

    Countries.forEach(Country =>{
        if (Country.checked){
            CountryData[Country.id] = true;
        }

    })


    const KitchenForm = document.getElementById('panel-collapseKitchen');
    const Kitchens = KitchenForm.querySelectorAll('input');

    const KitchenData = {}

    Kitchens.forEach(Kitchen =>{
        if (Kitchen.checked){
            KitchenData[Kitchen.id] = true;
        }

    })

    const VehicleForm = document.getElementById('panel-collapseVehicle');
    const Vehicles = VehicleForm.querySelectorAll('input');

    const VehicleData = {}

    Vehicles.forEach(Vehicle =>{
        if (Vehicle.checked){
            VehicleData[Vehicle.id] = true;
        }
    
    })

    const PriceRange = document.getElementById('Price-Range');
    const range = PriceRange.value;

    const FilterData = {}

    FilterData['CountryFilter'] = CountryData;
    FilterData['KitchenFilter'] = KitchenData;
    FilterData['VehicleFilter'] = VehicleData;
    FilterData['SearchBar'] = Searchbar;
    FilterData.range = range;

    fetchResults(FilterData);

}

function fetchResults(FilterData){


    console.log(FilterData);

    fetch("http://localhost:8080/filter-foodtrucks",{
        credentials: 'include',
        method: 'POST',
        headers: headers,
        body: JSON.stringify(FilterData)
    })
    .then(response => response.json())
    .then(data => {
        console.log('Response', data);
        headers.set('X-CSRF-TOKEN', data.newCSRFtoken);
        const CardSet = document.getElementById('FoodTruckSection');
        CardSet.innerHTML = ""; //Reset
        
        

        if(!data.FoodTrucks.length){
            const Column = document.createElement('div')
            Column.classList.add('col', 'd-flex',
            'justify-content-center', 'align-items-center', 'text-white');
    
            Column.style.height = "400px";
    
            const NoResultsFoundText = document.createElement('h1')
            NoResultsFoundText.innerHTML = "Oops, seems there are no results &#128517;";
            Column.appendChild(NoResultsFoundText);
            CardSet.appendChild(Column);
        }
        else{
            data.FoodTrucks.forEach(FoodTruck => {
                const Column = document.createElement('div')
                Column.classList.add('col-lg-3', 'col-md-6', 'col-sm-6', 'd-flex',
                'justify-content-center');
    
                const Card = document.createElement('div');
                Card.classList.add('card', 'shadow', 'FoodTruckCard');
                
                const CardBody = document.createElement('div');
                CardBody.classList.add('card-body');
    
            
    
    
                const MainImage = document.createElement('img');
    
                if (FoodTruck.Media != null){
                    MainImage.setAttribute('src', "img/" + FoodTruck.Media);
                }
                else{
                    MainImage.setAttribute('src', "staticimg/FoodtruckStaticIcon.png");
    
                }
    
                MainImage.classList.add('img-fluid', 'card-img-top');
                MainImage.setAttribute('Alt', 'Food truck Photo');
    
                const CardTitle = document.createElement('h5');
                CardTitle.classList.add('card-title');
                CardTitle.innerHTML = FoodTruck.Name;
    
                const CardText = document.createElement('p');
                CardText.classList.add('text-truncate');
                CardText.innerHTML = FoodTruck.Description;
    
                const Checkbutton = document.createElement('a');
                Checkbutton.setAttribute('href', "Foodtruckinfopage/" + FoodTruck.Name);
                Checkbutton.classList.add('btn','btn-primary', 'text-black', 'bg-white', 'border-black');
                Checkbutton.innerHTML = 'Check it out!'
    
                CardBody.appendChild(CardTitle);
                CardBody.appendChild(CardText);
                CardBody.appendChild(Checkbutton);
    
                Card.appendChild(MainImage);
                Card.appendChild(CardBody);
                Column.appendChild(Card);
                CardSet.appendChild(Column);
    
    
            });

    
        }
    
    })
    .catch(error => {
        console.error('Error:', error);
    });
    }
    



