import 'dart:ui';

import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';
import 'package:nobu/activity_limousine.dart';
import 'package:nobu/activity_restaurant.dart';
import 'package:nobu/activity_menu.dart';
import 'package:qr_flutter/qr_flutter.dart';
import 'Restaurant.dart';
import 'package:fluttertoast/fluttertoast.dart';

class ActivityPage extends StatefulWidget {
  final Restaurant restaurant;

  const ActivityPage({Key? key, required this.restaurant}) : super(key: key);

  @override
  State<ActivityPage> createState() => ActivityPageState();
}

class ActivityPageState extends State<ActivityPage> {
  String _selectedItem = 'LIMOUSINE'; // Default selected item
  String ConfirmationOfOrder = "Confirm order";

  StatefulWidget ChangeTab() {
    if (_selectedItem == 'LIMOUSINE') {
      return ActivityLimousinePage(key: UniqueKey());
    } else if (_selectedItem == 'RESTAURANT') {
      return ActivityRestaurantPage(
        key: UniqueKey(),
        restaurant: widget.restaurant,
      );
    } else {
      return ActivityMenuPage(key: UniqueKey());
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        leading: IconButton(
          icon: Icon(Icons.close),
          onPressed: () {
            Navigator.pop(context);
          },
          iconSize: 50.0,
        ),
        centerTitle: true, // Aligns title in the center
        title: DropdownButtonHideUnderline(
          child: Container(
            padding: EdgeInsets.only(top: 12), // Adjust the bottom padding as needed
            child: DropdownButton<String>(
              value: _selectedItem,
              onChanged: (String? newValue) {
                setState(() {
                  _selectedItem = newValue!;
                });
              },
              items: <String>['LIMOUSINE', 'RESTAURANT', 'MENU']
                  .map<DropdownMenuItem<String>>((String value) {
                return DropdownMenuItem<String>(
                  value: value,
                  child: Text(
                    value,
                    style: TextStyle(
                      fontSize: 28, // Adjusts the font size
                    ),
                  ),
                );
              }).toList(),
            ),
          ),
        ),
      ),
      body: Center(
        child: ChangeTab(),
      ),
      floatingActionButton: _selectedItem != 'MENU' ? FloatingActionButton(
        onPressed: () {
          showModalBottomSheet(
            showDragHandle: true,
            context: context,
            builder: (BuildContext context) {
              return Container(
                child: Column(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    
                    Expanded(
                      child: ListView(
                        shrinkWrap: true,
                        physics: BouncingScrollPhysics(),
                        children: [
                          Container(
                            padding: EdgeInsets.all(60.0),
                            child: Column(
                              mainAxisSize: MainAxisSize.min,
                              children: [
                                QrImageView(
                                  data: "data",
                                  version: QrVersions.auto,
                                  size: 260.0,
                                ),
                                SizedBox(height: 20.0),
                                Text(
                                  'Show this QR-code when asked to',
                                  style: TextStyle(fontSize: 18.0),
                                ),
                              ],
                            ),
                          ),
                        ],
                      ),
                    ),
                  ],
                ),
              );
            },
          );
        },
        backgroundColor: Colors.blue.shade300,
        shape: CircleBorder(),
        child: Transform.scale(
          scale: 1.5,
          child: Icon(Icons.qr_code_2),
        ),
      ) : Column(
        mainAxisAlignment: MainAxisAlignment.end,
        children: [

          FloatingActionButton(
            onPressed: () {
              
              showModalBottomSheet(
                          showDragHandle: true,
                          context: context,
                          
                          builder: (BuildContext context) {
                            return Column(
                              children: [
                                Expanded(
                                  child: ListView(
                                    shrinkWrap: true,
                                    children: [
                                      Container(
                                        padding: EdgeInsets.all(10.0),
                                        child: Column(
                                          children: [
                                            ElevatedButton(
                                              onPressed: (){
                                                context.pop();
                                                setState(() {
                                                  ConfirmationOfOrder = "✓ Confirmed!";
                                                });
                                              },
                                              style: ElevatedButton.styleFrom(backgroundColor: Colors.blue.shade100, elevation: 10), 
                                              child: Text(
                                                ConfirmationOfOrder,
                                                style: TextStyle(color: Colors.black),
                                              ),
                                              ),
                                              DataTable(columns: [
                                                
                                                DataColumn(label: Text("Menu")),
                                                DataColumn(label: Text("Type")),
                                                DataColumn(label: Text("Specification")),
                                                DataColumn(label: Text("")),
                                              ], 
                                              dataRowMaxHeight: 100,
                                              dataRowMinHeight: 50,
                                              columnSpacing: 5,
                                              rows: [
                                                DataRow(cells: 
                                                [
                                                  DataCell(Text("Green Tea")),
                                                  DataCell(Text("Drink")),
                                                  DataCell(Text("Tea")),
                                                  DataCell(IconButton(icon: Icon(Icons.remove_circle_outline_sharp,), onPressed: (){},))
                                                ]),
                                                                                                DataRow(cells: 
                                                [
                                                  DataCell(Text("Grilled octopus with chorizo oil and caramelized onion")),
                                                  DataCell(Text("Food")),
                                                  DataCell(Text("5-course")),
                                                  DataCell(IconButton(icon: Icon(Icons.remove_circle_outline_sharp,), onPressed: (){},))
                                                ]),
                                                                                                DataRow(cells: 
                                                [
                                                  DataCell(Text("Tiramisu with a twist of orange and amaretto")),
                                                  DataCell(Text("Food")),
                                                  DataCell(Text("5-course")),
                                                  DataCell(IconButton(icon: Icon(Icons.remove_circle_outline_sharp,), onPressed: (){},))
                                                ]),
                                                                                                DataRow(cells: 
                                                [
                                                  DataCell(Text("Herbal Tea")),
                                                  DataCell(Text("Drink")),
                                                  DataCell(Text("Tea")),
                                                  DataCell(IconButton(icon: Icon(Icons.remove_circle_outline_sharp,), onPressed: (){},))
                                                ]),
                                                                                                DataRow(cells: 
                                                [
                                                  DataCell(Text("Spaghetti Bolognese")),
                                                  DataCell(Text("Food")),
                                                  DataCell(Text("Pasta")),
                                                  DataCell(IconButton(icon: Icon(Icons.remove_circle_outline_sharp,), onPressed: (){},))
                                                ]),
                                              ]
                                              )
                                            
                                            
                                          ],
                                        ),
                                      ),
                                    ],
                                  ),
                                ),
                              ],
                            );
                          },
                        );
              
            },
            backgroundColor: Colors.blue, // Stel de kleur van de knop in op rood
            shape: CircleBorder(),
            child: Transform.scale(
              scale: 1.5,
              child: Icon(Icons.table_chart_outlined),
            ),
          ),
          SizedBox(height: 10),
          FloatingActionButton(
            onPressed: () {
              Fluttertoast.showToast(
                msg: "Your server will be with you shortly",
                toastLength: Toast.LENGTH_SHORT,
                gravity: ToastGravity.CENTER,
                timeInSecForIosWeb: 5,
                backgroundColor: Colors.red.shade300,
                textColor: Colors.black,
                fontSize: 22.0,
              );
            },
            backgroundColor: Colors.red.shade200,
            shape: CircleBorder(),
            child: Transform.scale(
              scale: 1.5,
              child: Icon(Icons.room_service),
            ),
          )
        ],
      ) 
      
      
      
    );
  }
}