import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';
import 'package:faker/faker.dart';
import 'FavoritesState.dart';
import 'Restaurant.dart';
import 'package:provider/provider.dart';
// ignore: use_key_in_widget_constructors, camel_case_types

class SearchResultsPage extends StatefulWidget {


  SearchResultsPage({required key});

  @override
  State<SearchResultsPage> createState() => SearchResultsPageState();
}

class SearchResultsPageState extends State<SearchResultsPage> {

  static final List<String> Locations = List.generate(10, (index) => "${faker.address.city()}, ${faker.address.country()}");
  static final List<String> Cuisines = List.generate(10, (index) => "${faker.food.cuisine()}");
  List<bool> _isFavoritedList = List.filled(20, false);

  List<Restaurant> restaurants = List.generate(
    10,
        (index) => Restaurant(
      index,
      faker.food.restaurant(),
      faker.food.cuisine(),
      faker.randomGenerator.integer(50) / 10,
    ),
  );

  @override
  Widget build(BuildContext context) {
    return Scaffold(

      body: Center(
        child:Stack(
          children: [
            Padding(
              padding: const EdgeInsets.fromLTRB(5, 40, 5, 0),
              child: Row(
                children: [
                  Expanded(child: SearchBar()),
                  Padding(
                    padding: const EdgeInsets.fromLTRB(5, 0, 5, 0),
                    child: IconButton(
                      icon : Icon(Icons.search, size: 30, color: Colors.black),
                      onPressed: (){},
                      style: ElevatedButton.styleFrom(shape : CircleBorder(), backgroundColor: Colors.blue.shade100)
                                    ),
                  ),
                  Builder(
                        builder: (context) => IconButton(
                        icon: Icon(Icons.filter_alt, size: 30, color: Colors.black),
                        onPressed: () {
                          Scaffold.of(context).openEndDrawer();
                        },
                        style: ElevatedButton.styleFrom(
                          shape: CircleBorder(),
                          backgroundColor: Colors.blue.shade100,
                        ),
                      ),
                  ),
                ],
              ),
            ),
            Center(
              child: Padding(
                padding: const EdgeInsets.fromLTRB(5, 110, 5, 0),
                child: SingleChildScrollView(
                  child: Column(
                    children: restaurants.map((restaurant) {
                      return Padding(
                        padding: const EdgeInsets.all(8.0),
                        child: _buildRestaurantItem(context, restaurant),
                      );
                    }).toList(),
                  ),
                ),
              ),
            )
        ],)
      ),
      endDrawer: _buildDrawer(context),
    );
  }

  Widget _buildRestaurantItem(BuildContext context, Restaurant restaurant) {
    FavoritesState favoritesState = Provider.of<FavoritesState>(context);

    return GestureDetector(
      onTap: () {
        context.push(context.namedLocation("RestaurantInfo"));
      },
      child: Container(
      margin: EdgeInsets.symmetric(horizontal: 12.0),
      width: 500.0,
      decoration: BoxDecoration(
        color: Colors.grey[300],
        borderRadius: BorderRadius.circular(10.0),
      ),
      child: SingleChildScrollView(
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.center,
            children: [
              ClipRRect(
                borderRadius: BorderRadius.circular(10.0),
                child: Image.asset(
                  'assets/images/luminoso.jpg',
                  width: 500.0,
                  height: 200.0,
                  fit: BoxFit.cover,
                ),
              ),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: [
                Padding(
                  padding: EdgeInsets.only(left: 10.0),
                  child: Text(
                    restaurant.name,
                    style: TextStyle(
                      fontSize: 16.0,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ),
                Padding(
                  padding: EdgeInsets.only(right: 1.0),
                  child: IconButton(
                    onPressed: () {
                      setState(() {
                        favoritesState.toggleFavorite(restaurant);
                        final isFavorited = favoritesState.favorites.containsKey(restaurant.index);
                        _isFavoritedList[restaurant.index] = isFavorited;
                      });

                    },
                    icon: Icon(
                      _isFavoritedList[restaurant.index] ? Icons.favorite : Icons.favorite_border,
                      color: _isFavoritedList[restaurant.index] ? Colors.red : null,
                      size: 26.0,
                    ),
                  ),
                ),
              ],
            ),
            Padding(
              padding: EdgeInsets.only(left: 10.0),

              child: Row(
                children: [
                  Text(
                    '${restaurant.cuisine} - ',
                    style: TextStyle(
                      fontSize: 14.0,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                  Text(
                    '★ ${restaurant.rating}',
                    style: TextStyle(
                      fontSize: 14.0,
                      fontWeight: FontWeight.bold,
                    ),
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    ),
    );
  }

  Widget _buildDrawer(BuildContext context){
    return Drawer(
      child: ListView(

        children:  [

          //HeadText:
          Padding(
            padding: const EdgeInsets.all(10),

            child: Column(
            children: [
              Text(
                "Filters",
                style: TextStyle(
                  fontWeight: FontWeight.bold,
                  fontSize: 30
                ), 
              )
            ]
                    ),
          ),


          Padding(
            padding: const EdgeInsets.all(20),

            
            child: Card(
              elevation: 20, 
              shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(120.0),
              
              ),
              child: SizedBox(
                height: 50,  
                child: Row(
                  
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    Icon(Icons.people_outline, size: 30, color: Colors.black),
                    IconButton(onPressed: (){}, icon: Icon(Icons.arrow_back_ios_new_sharp), iconSize: 20, color: Colors.black),
                    Text(String.fromCharCode(49),  style: TextStyle(fontSize: 20)),
                    IconButton(onPressed: (){}, icon: Icon(Icons.arrow_forward_ios_sharp), iconSize: 20, color: Colors.black),
                  ],
                )
              ),
            ),
          ),

          //Location
          Padding(
            padding: const EdgeInsets.all(25.0),
            child: SizedBox(
              height: 60.0,

              child: Card(
                elevation: 20,
                color: Colors.white,
                shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(120.0),
              
              ),

                child: Padding(
                  padding: const EdgeInsets.fromLTRB(10, 0, 0, 0),
                  child: Autocomplete<String>(
                  optionsBuilder: (TextEditingValue input) {
                    if (input == ""){
                      return const Iterable<String>.empty();
                    }
                    return Locations.where((String location) {return location.toLowerCase().contains(input.text.toLowerCase());});
                  },
                  fieldViewBuilder: (BuildContext context, TextEditingController textEditingController,
                              FocusNode focusNode, VoidCallback onFieldSubmitted) {
                            return TextField(
                              controller: textEditingController,
                              focusNode: focusNode,
                              decoration: InputDecoration(
                                hintText: "Location",
                                hintStyle: TextStyle(fontSize: 20, fontWeight: FontWeight.bold), 
                                border: InputBorder.none
                                
                              ),
                              onChanged: (value) {
                                onFieldSubmitted();
                              },
                            );
                          }
                  ),
                ),
              ),
            ),
          ),

          //Date
          Padding(
            padding: const EdgeInsets.all(25),

            child: SizedBox(
              height: 60.0,
              child: ElevatedButton.icon(
                onPressed: () {
                    showDialog(
                    context: context,
                    builder: (context){ return _buildDateDialog(context);}
                  );
                },
                label: const Text("Date", style: TextStyle(fontSize: 20)),
                icon: Icon(Icons.calendar_month, size: 30,),
                style:ElevatedButton.styleFrom(backgroundColor: Colors.white, elevation: 20, foregroundColor: Colors.black)
              ),
            ),
          ),

          //Time
          Padding(
            padding: const EdgeInsets.all(25),
            child: SizedBox(
              height: 60.0,
              child: ElevatedButton.icon(

                onPressed: () {
                  showDialog(
                    context: context,
                    builder: (context){ return _buildTimeDialog(context);}
                  );
                },
                label: const Text("Time", style: TextStyle(fontSize: 20)),
                icon: Icon(Icons.access_time_outlined, size:30),
                style:ElevatedButton.styleFrom(backgroundColor: Colors.white, elevation: 20, foregroundColor: Colors.black)
              ),
            ),
          ),

         //Cuisine
          Padding(
            padding: const EdgeInsets.all(20),
            child: Card(
                elevation: 20,
                color: Colors.white,
                shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(120.0)),
              child: Padding(
                padding: const EdgeInsets.fromLTRB(10,0,0,0),
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children:[
                    Icon(
                      Icons.food_bank_rounded,
                      size: 40),
                    SizedBox(width: 10),
                    DropdownMenu(
                      label: Text("Cuisine", style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold, color: Colors.black)),
                      inputDecorationTheme:InputDecorationTheme(border: InputBorder.none),
                      width: 150,
                      dropdownMenuEntries: Cuisines.map((cuisine) {
                      return DropdownMenuEntry(value: cuisine, label: cuisine);
                      }).toList()
                    ),
                  ]
                ),
              ),
            ),
          ),

        //Minimumrating
          Padding(
            padding: const EdgeInsets.all(20),
            child: Card(
                elevation: 20,
                color: Colors.white,
                shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(120.0)),
              child: Padding(
                padding: const EdgeInsets.fromLTRB(10,0,0,0),
                child: Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children:[
                    Icon(
                      Icons.star_border,
                      size: 40),
                    SizedBox(width: 10),
                    DropdownMenu(
                      label: Text("Min. Rating", style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold, color: Colors.black)),
                      inputDecorationTheme:InputDecorationTheme(border: InputBorder.none),
                      width: 150,
                      dropdownMenuEntries: [
                        DropdownMenuEntry(value: Colors.white, label: "5"),
                        DropdownMenuEntry(value: Colors.white, label: "4 and more"),
                        DropdownMenuEntry(value: Colors.white, label: "3 and more"),
                        DropdownMenuEntry(value: Colors.white, label: "2 and more"),
                        DropdownMenuEntry(value: Colors.white, label: "1 and more")
                      ]
                    ),
                  ]
                ),
              ),
            ),
          ),

          //Save/Close
          Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
            Padding(
              padding: const EdgeInsets.all(10.0),
              child: ElevatedButton(
                onPressed: (){
                  context.pop();
                },
                style: ElevatedButton.styleFrom(backgroundColor: Colors.blue.shade100, elevation: 10), 
                child: Text(
                  "Save",
                  style: TextStyle(color: Colors.black),
                ),
              ),
            ),

            Padding(
              padding: const EdgeInsets.all(10.0),
              child: ElevatedButton(
                onPressed: (){
                  context.pop();
                },
                style: ElevatedButton.styleFrom(backgroundColor: Colors.blue.shade100, elevation: 10), 
                child: Text(
                  "Cancel",
                  style: TextStyle(color: Colors.black),
                ),
              ),
            ),
          ],)
        ]
      )
    );
  }

  Widget _buildTimeDialog(BuildContext context) {
  return TimePickerDialog(initialTime: TimeOfDay.now());
}


Widget _buildDateDialog(BuildContext context) {
  return DatePickerDialog(
    firstDate: DateTime(2000),
    lastDate: DateTime(3000),
    selectableDayPredicate: (DateTime date) {
        return !date.isBefore(DateTime.now());
    },
  );
}
}


