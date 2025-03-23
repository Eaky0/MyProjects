import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';
import 'dart:math';
import 'package:nobu/Restaurant.dart';
import 'activity.dart';

// ignore: use_key_in_widget_constructors, camel_case_types
class ReservationListPage extends StatefulWidget {

  const ReservationListPage({required key});

  @override
  State<ReservationListPage> createState() => ReservationListPageState();
}

class ReservationListPageState extends State<ReservationListPage> {


  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        backgroundColor: Colors.white,
        body: Stack(
          children: [
            _buildAppBar(),
            Padding(
              padding: const EdgeInsets.fromLTRB(0, 110, 0, 0),
              child: Divider(color: Colors.black),
            ),
            Center(
              child: Padding(
                padding: const EdgeInsets.fromLTRB(5, 120, 5, 0),
                child: SingleChildScrollView(
                  child: Column(
                      children: [
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child : _buildUpcomingReservation(context, Restaurant(2, "Sushi Haven", "Japanese", 4.8), "Active"),
                        ),
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: _buildUpcomingReservation(context, Restaurant(4, "Le Petit Bistro", "French", 4.4), "Active"),

                        ),
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child:_buildUpcomingReservation(context, Restaurant(1, "Bella Italia", "Italian", 4.2), "14d 15h 20m 25s"),

                        ),
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: _buildUpcomingReservation(context, Restaurant(3, "The Steakhouse", "American", 4.6), "16d 05h 45m 35s"),
                        ),
                        Padding(
                            padding: const EdgeInsets.all(8.0),
                            child: _buildUpcomingReservation(context, Restaurant(5, "El Mariachi", "Mexican", 4.3), "18d 30h 10m 45s")
                        ),
                      ]
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildAppBar() {
    return Row(
        children:[
          IconButton(onPressed: (){context.pop();}, icon: Icon(Icons.navigate_before), iconSize: 50,),
          SizedBox(width: 5),
          Container(
            height: 120.0,
            alignment: Alignment.center,
            child: Text(
              '~ NOBU ~',
              style: TextStyle(
                fontFamily: 'Pilgrim',
                fontSize: 55.0,
              ),
            ),
          ),
        ]
    );
  }

  Widget _buildUpcomingReservation(BuildContext context, Restaurant r, String time){

    bool isCollapsed = false;

    return Column(
      children: [
        Padding(
          padding: const EdgeInsets.all(8.0),
          child: Card(
            color: Colors.blue.shade50, // Achtergrondkleur van de kaart
            elevation: 20,
            child: Column(
                children: [
                  Padding(
                      padding: const EdgeInsets.fromLTRB(10, 10, 0, 20),
                      child: Row(
                        children: [
                          Icon(Icons.timer),
                          SizedBox(width: 10,),
                          Text(time),
                          Spacer(),
                          if (time == "Active")
                            ElevatedButton(
                              onPressed: () {
                                Navigator.push(
                                  context,
                                  MaterialPageRoute(
                                    builder: (context) => ActivityPage(restaurant: r),
                                  ),
                                );
                              },
                              child: Text(
                                "Continue",
                                style: TextStyle(
                                  fontSize: 13,
                                  color: Colors.black, // Tekstkleur van de knop
                                ),
                              ),
                            ),
                          SizedBox(width: 20),
                        ],
                      )
                  ),
                  Theme(
                    data: ThemeData(
                      expansionTileTheme: ExpansionTileThemeData(
                        shape: ContinuousRectangleBorder(borderRadius: BorderRadius.zero),
                      ),
                    ),
                    child: ExpansionTile(
                      title: Text(
                        r.name,
                        style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 20
                        ),
                      ),
                      onExpansionChanged: (bool expanded){
                        print("Expansion state changed: $expanded");
                        setState(() =>isCollapsed = expanded);
                      },

                      children: [
                        SizedBox(
                          width: 450.0,
                          height: 200.0,
                          child: Image.asset(
                            'assets/images/luminoso.jpg',
                            fit: BoxFit.cover,
                          ),
                        ),
                        Padding(
                          padding: const EdgeInsets.fromLTRB(20, 20, 20, 5),
                          child: Row(
                            children: [
                              Text("Date", style: TextStyle(
                                fontStyle: FontStyle.italic,
                              ),),
                              Spacer(),
                              Text("14/05/2024"),
                              SizedBox(width: 130,)
                            ],
                          ),
                        ),
                        Padding(
                          padding: const EdgeInsets.fromLTRB(20, 5, 20, 5),
                          child: Row(
                            children: [
                              Text("Time", style: TextStyle(
                                fontStyle: FontStyle.italic,
                              ),),
                              Spacer(),
                              Text("19:00"),
                              SizedBox(width: 130,)
                            ],
                          ),
                        ),
                        Padding(
                          padding: const EdgeInsets.fromLTRB(20, 5, 20, 5),
                          child: Row(
                            children: [
                              Text("Party size", style: TextStyle(
                                fontStyle: FontStyle.italic,
                              ),),
                              Spacer(),
                              Text("3"),
                              SizedBox(width: 130,)
                            ],
                          ),
                        ),
                        Padding(
                          padding: const EdgeInsets.fromLTRB(20, 5, 20, 5),
                          child: Row(
                            children: [
                              Text("Limousine?", style: TextStyle(
                                fontStyle: FontStyle.italic,
                              ),),
                              Spacer(),
                              Text("Yes"),
                              SizedBox(width: 130,)
                            ],
                          ),
                        ),

                        Padding(
                          padding: const EdgeInsets.fromLTRB(20, 5, 20, 5),
                          child: Row(
                            children: [
                              Text("Companions", style: TextStyle(
                                fontStyle: FontStyle.italic,
                              ),),
                              Spacer(),
                              Icon(Icons.person),
                              Text("Karen Damen"),
                              SizedBox(width: 87)
                            ],
                          ),
                        ),

                        Padding(
                          padding: const EdgeInsets.fromLTRB(20, 0, 20, 5),
                          child: Row(
                            children: [
                              Spacer(),
                              Icon(Icons.help),
                              Text("kathleen.aerts@gmail.com", overflow: TextOverflow.ellipsis,),
                            ],
                          ),
                        ),
                      ],
                    ),
                  ),
                ]
            ),
          ),
        ),
      ],
    );
  }
}