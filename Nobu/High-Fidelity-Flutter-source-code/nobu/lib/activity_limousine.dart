import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';


// ignore: use_key_in_widget_constructors, camel_case_types
class ActivityLimousinePage extends StatefulWidget {

  const ActivityLimousinePage({required key});

  @override
  State<ActivityLimousinePage> createState() => _ActivityLimousinePage();
}

class _ActivityLimousinePage extends State<ActivityLimousinePage> {
  bool value = true;

  Widget ChangeTab(){
      if (value){
        return _buildOutbound(context);
      }
      else{
        return _buildReturn(context);
      }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Stack(
        children: [
      
          //Citatie:
          //https://stackoverflow.com/questions/75066001/how-to-add-text-inside-cupertino-switch-flutter
          GestureDetector(
            
                
                onTap: () {
                  setState(() {
                    value = !value;
                  });
                },
                
                child: Padding(
                  padding: const EdgeInsets.fromLTRB(110, 8, 0, 8),
                  child: Container(
                    width: MediaQuery.of(context).size.width * 0.40,
                    decoration: BoxDecoration(
                        borderRadius: BorderRadius.circular(30),
                        color: Colors.brown.shade100),
                    child: Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: Row(
                        mainAxisAlignment:
                            MainAxisAlignment.spaceBetween,
                        children: [
                          Container(
                            width: 70,
                            height: 30,
                            decoration: BoxDecoration(
                                borderRadius:
                                    BorderRadius.circular(30),
                                color: value
                                    ? Colors.white
                                    : Colors.brown.shade100),
                            child: Center(
                                child: Text(
                              'Outbound',
                              style: TextStyle(
                                  fontWeight: FontWeight.bold,
                                  color: value
                                      ? Colors.black
                                      : Colors.white),
                            )),
                          ),
                          Container(
                            width: 70,
                            height: 30,
                            decoration: BoxDecoration(
                                borderRadius:
                                    BorderRadius.circular(30),
                                color: value
                                    ? Colors.brown.shade100
                                    : Colors.white),
                            child: Center(
                                child: Text(
                              'Return',
                              style: TextStyle(
                                  fontWeight: FontWeight.bold,
                                  color: value
                                      ? Colors.white
                                      : Colors.black),
                            )),
                          ),
                        ],
                      ),
                    ),
                  ),
                ),
              ),
              ChangeTab(),
          
      
      ],)
    );
  }


  Widget _buildOutbound(context){
    return Padding(
      padding: const EdgeInsets.fromLTRB(0, 60, 0,0),
      child: SingleChildScrollView(
        child: Column(
          children: [
            _buildLocationCollapse(context),
            _buildAperitifCollapse(context),
            SizedBox(height: 100,)
          ],
        ),
      ),
    );

  }


  Widget _buildLocationCollapse(context){
    bool isCollapsed = false;

    return Column(
      children: [
        Padding(
          padding: const EdgeInsets.all(8.0),
          child: Card(
            color: Colors.blue.shade50, // Background color of the card
            elevation: 20,
            child: Column(
              children: [
                Theme(
                  data: ThemeData(
                    expansionTileTheme: ExpansionTileThemeData(
                      shape: ContinuousRectangleBorder(borderRadius: BorderRadius.zero),
                    ),
                  ),
                  child: ExpansionTile(
                    title: Text(
                      "Location",
                      style: TextStyle(
                        fontWeight: FontWeight.bold,
                        fontSize: 20,
                      ),
                    ),
                    onExpansionChanged: (bool expanded) {
                      setState(() => isCollapsed = expanded);
                    },
                    children: [
                      Column(

                        children: [
                          Padding(
                            padding: const EdgeInsets.all(8.0),
                            
                            child: Container(
                              decoration: BoxDecoration(
                                border: Border.all(
                                color: Colors.black,
                                width: 2.0,
                              ),
                              ),
                              width: 350.0,
                              height: 300.0,
                              child: Image.asset(
                                'assets/images/limoReturn.jpg',
                                fit: BoxFit.cover,
                              ),
                            )

                          ),    
                          SizedBox(height: 20,),
                          Text(
                            "Time left for arrival:",
                            style: TextStyle(
                              fontStyle: FontStyle.italic,
                              fontSize: 20
                            ), 
                          ),
                          Text(
                            "0h 20m 25s",
                            style: TextStyle(
                              fontWeight: FontWeight.bold,
                              fontSize: 30
                            ), 
                          ),
                          SizedBox(height: 20,),


                        ],

                      ),
                    ],
                  ),
                ),
              ],
            ),
          ),
        ),
      ],
    );    
  }

 Widget _buildAperitifCollapse(context){
    bool isCollapsed = false;

    return Column(
      children: [
        Padding(
          padding: const EdgeInsets.all(8.0),
          child: Card(
            color: Colors.blue.shade50, // Background color of the card
            elevation: 20,
            child: Column(
              children: [
                Theme(
                  data: ThemeData(
                    expansionTileTheme: ExpansionTileThemeData(
                      shape: ContinuousRectangleBorder(borderRadius: BorderRadius.zero),
                    ),
                  ),
                  child: ExpansionTile(
                    title: Text(
                      "Aperitif",
                      style: TextStyle(
                        fontWeight: FontWeight.bold,
                        fontSize: 20,
                      ),
                    ),
                    onExpansionChanged: (bool expanded) {
                      setState(() => isCollapsed = expanded);
                    },
                    children: [
                      Column(

                        children: [
                          Padding(
                            padding: const EdgeInsets.all(8.0),
                            
                            child: Container(
                              decoration: BoxDecoration(
                                border: Border.all(
                                color: Colors.black,
                                width: 2.0,
                              ),
                              ),
                              width: 350.0,
                              height: 300.0,
                              child: Image.asset(
                                'assets/images/DomPerignon.jpg',
                                fit: BoxFit.cover,
                              ),
                            )

                          ),    
                          Text(
                            "Dom Pérignon",
                            style: TextStyle(
                              fontWeight: FontWeight.bold,
                              fontSize: 30
                            ), 
                          ),
                          Text(
                            "Dom Pérignon is a prestigious brand of vintage champagne. Named after Dom Pérignon, ...",
                            textAlign: TextAlign.center,
                            style: TextStyle(
                              fontSize: 15
                            ), 
                          ),
                          Row(
                    children: [
                      Spacer(),
                      IconButton(onPressed: (){
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
                                        padding: EdgeInsets.all(60.0),
                                        child: Column(
                                          children: [
                                            Container(
                                              width: 450.0,
                                              height: 200.0,
                                              child: Image.asset(
                                                'assets/images/food3.jpg',
                                                fit: BoxFit.cover,
                                              ),
                                            ),
                                            
                                          SizedBox(height: 20),
                                          SizedBox(height: 20,),
                                          Text(
                                          "Dom Pérignon is a prestigious brand of vintage champagne. Named after Dom Pérignon, a Benedictine monk credited with several innovations in champagne production in the late 17th century, the Dom Pérignon champagne house, part of the luxury conglomerate Moët & Chandon, produces only vintage champagne, made exclusively from grapes of a single harvest year.Dom Pérignon champagnes are considered some of the finest in the world due to their exceptional quality and craftsmanship. They are often associated with luxury events and special occasions. Dom Pérignon is known for its complex flavors, fine bubbles, and ability to mature with age, making it a favorite among connoisseurs and champagne enthusiasts. Dom Pérignon champagne traces its origins to the Champagne region of France, an area globally renowned for its high-quality sparkling wines. The history of Dom Pérignon dates back to the 17th century when the Benedictine monk Dom Pérignon worked at the abbey of Hautvillers.",
                                          style: TextStyle(
                                            fontSize: 15, 
                                            overflow: TextOverflow.clip                                              
                                          ),)  
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


                      }, icon: Icon(Icons.info_outline)),
                    ],
                  )

                        ],

                      ),
                    ],
                  ),
                ),
              ],
            ),
          ),
        ),
      ],
    );    
  }

  




  Widget _buildReturn(context){
    return Padding(
      padding: const EdgeInsets.fromLTRB(0, 60, 0,0),
      child: SingleChildScrollView(
        child: Column(
          children: [
            _buildLocationCollapse(context),
          ],
        ),
      ),
    );
  }



}
