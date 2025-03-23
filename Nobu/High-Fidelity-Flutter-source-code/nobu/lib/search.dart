
import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';
import 'package:faker/faker.dart';
import 'package:nobu/nav.dart';
import 'restaurantInfo.dart';
import 'searchresults.dart';


class SearchPage extends StatefulWidget{
  const SearchPage({required key});

  @override
  State<SearchPage> createState() => _search();

}



// ignore: use_key_in_widget_constructors, camel_case_types
class _search extends State<SearchPage> {

  int count = 1;

  final faker = Faker();



  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: ListView(
        physics: NeverScrollableScrollPhysics(),

        children:  [

          //HeadText:
          Padding(
            padding: const EdgeInsets.fromLTRB(10, 20, 10, 20),
            child: Column(
            children: [
              Text(
                "Find a Restaurant",
                style: TextStyle(
                  fontWeight: FontWeight.bold,
                  fontSize: 30
                ), 
              )
            ]
                    ),
          ),


          //Amount of Guests
          Padding(
            padding: const EdgeInsets.fromLTRB(10, 20, 10, 20),
            
            child: Card(
              color: Colors.white,
              elevation: 20, 
              shape: RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(120.0),
              
              ),
              child: SizedBox(
                height: 100,  
                child: Row(
                  
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    Icon(Icons.people_outline, size: 40, color: Colors.black),
                    IconButton(onPressed: (){}, icon: Icon(Icons.arrow_back_ios_new_sharp), iconSize: 30, color: Colors.black),
                    Text(String.fromCharCode(count + 48),  style: TextStyle(fontSize: 40)),
                    IconButton(onPressed: (){}, icon: Icon(Icons.arrow_forward_ios_sharp), iconSize: 30, color: Colors.black),
                  ],
                  
                )
                ),
              ),
            ),
          
          

          //Location
          Padding(
            padding: const EdgeInsets.fromLTRB(10, 20, 10, 20),
          
            child: SizedBox(              
              height: 100.0,
              
              child: ElevatedButton.icon(
                onPressed: () {
                  showDialog(
                    context: context,
                    builder: (context) {return _buildLocationDialog(context);}
                  );
                },
                label: const Text("Location", style: TextStyle(fontSize: 30)),
                icon: Icon(Icons.fmd_good_outlined, size: 40,),
                style:ElevatedButton.styleFrom(backgroundColor: Colors.white, elevation: 20, foregroundColor: Colors.black)
                
              ),
            ),
          ),
          

          //Date
          Padding(
            padding: const EdgeInsets.fromLTRB(10, 20, 10, 20),
            child: SizedBox(
              height: 100.0,
              child: ElevatedButton.icon(
                onPressed: () {
                    showDialog(
                    context: context,
                    builder: (context){ return _buildDateDialog(context);}
                  );

                },
                label: const Text("Date", style: TextStyle(fontSize: 30)),
                icon: Icon(Icons.calendar_month, size: 40,),
                style:ElevatedButton.styleFrom(backgroundColor: Colors.white, elevation: 20, foregroundColor: Colors.black)
              ),
            ),
          ),

          //Time
          Padding(
            padding: const EdgeInsets.fromLTRB(10, 20, 10, 20),
            
            child: SizedBox(
              height: 100.0,
              child: ElevatedButton.icon(

                onPressed: () {
                  showDialog(
                    context: context,
                    builder: (context){ return _buildTimeDialog(context);}
                  );
                },
                label: const Text("Time", style: TextStyle(fontSize: 30)),
                icon: Icon(Icons.access_time_outlined, size:40),
                style:ElevatedButton.styleFrom(backgroundColor: Colors.white, elevation: 20, foregroundColor: Colors.black)
              ),
            ),
          ),
          

          //Search button
          Padding(
            padding: const EdgeInsets.fromLTRB(10, 0, 10, 0),
            child: SizedBox(
              height: 100.0,
              child: Transform(
                alignment: Alignment.center,
                transform: Matrix4.diagonal3Values(-1, 1, 1),
                child: IconButton(
                    icon : Icon(Icons.search, size: 75, color: Colors.black),
                    onPressed: () {
                          context.goNamed("SearchResults");
                        },
                    style: ElevatedButton.styleFrom(shape : CircleBorder(), backgroundColor: Colors.blue.shade100)
                ),
              ),
            ),
          ),

        ]
      )
    );
  }


  // ignore: non_constant_identifier_names
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


  Widget _buildLocationDialog(BuildContext context){
    return AlertDialog(
      actions: [
        TextButton(
          onPressed: (){Navigator.of(context).pop();}, 
          child: const Text("Cancel"))
      ],
      title: const Text("Location"),
      contentPadding: EdgeInsets.all(10.0),
      content: Stack(
      children: [
            Positioned(
              child: Padding(
                padding: const EdgeInsets.fromLTRB(0, 60, 0, 0),
                child: SingleChildScrollView(
                  child: Column(
                    children: List.generate(
                      30, 
                      (index) => GestureDetector(
                        onTap: () {
                          Navigator.of(context).pop();
                        },
                        child: Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: Container(
                            decoration: BoxDecoration(
                              color: Colors.blue.shade100,
                              border: Border.all(color: Colors.black),
                              borderRadius: BorderRadius.circular(15),
                            ),
                            child: SizedBox(
                              width: 300,
                              height: 50,
                              child: Row(
                                mainAxisAlignment: MainAxisAlignment.center,
                                
                                children: [
                                  Flexible(
                                    child: Text(
                                      "${faker.address.city()}, ${faker.address.country()}",
                                      overflow: TextOverflow.ellipsis
                                    ),
                                  )],
                              ),
                            ),
                          ),
                        ),
                      ),
                    ),
                  ),
                ),
              ),
            ),
            Positioned(
              top: 0,
              left: 0,
              right: 0,
              child: SearchBar(),
            ),
          ],
        ),
    );
  }
}





