import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';


// ignore: use_key_in_widget_constructors, camel_case_types
class ActivityMenuPage extends StatefulWidget {

  const ActivityMenuPage({required key});

  @override
  State<ActivityMenuPage> createState() => _ActivityMenuPage();
}

class _ActivityMenuPage extends State<ActivityMenuPage> {

  bool value = true;


  Widget ChangeTab(){
    if (!value){
      return _buildDrinkTab(context);
    }
    else{
      return _buildFoodTab(context);
    }
  }


  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Stack(
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
                    padding: const EdgeInsets.fromLTRB(130, 8, 0, 8),
                    child: Container(
                      width: MediaQuery.of(context).size.width * 0.35,
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
                              width: 60,
                              height: 30,
                              decoration: BoxDecoration(
                                  borderRadius:
                                      BorderRadius.circular(30),
                                  color: value
                                      ? Colors.white
                                      : Colors.brown.shade100),
                              child: Center(
                                  child: Text(
                                'Food',
                                style: TextStyle(
                                    fontWeight: FontWeight.bold,
                                    color: value
                                        ? Colors.black
                                        : Colors.white),
                              )),
                            ),
                            Container(
                              width: 60,
                              height: 30,
                              decoration: BoxDecoration(
                                  borderRadius:
                                      BorderRadius.circular(30),
                                  color: value
                                      ? Colors.brown.shade100
                                      : Colors.white),
                              child: Center(
                                  child: Text(
                                'Drinks',
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
      )
    );
  }


    Widget _buildDrinkTab(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.fromLTRB(0,50,0,0),
      child: Column(
            children: [
              _buildDrinkPreferenceTab(context),
              SizedBox(height: 20),
              Expanded(
                child: SingleChildScrollView(
                  scrollDirection: Axis.vertical,
                  child: Column(
                    children: [
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Text(
                          "Wine",
                          style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 20,
                            
                          ),
                        ),
                    ],
                  ),
                      
                    _DrinkItem(context, "Malbec"),
                    _DrinkItem(context, "Chardonnay"),
                    _DrinkItem(context, "Pinot Noir"),
                    _DrinkItem(context, "Sauvignon Blanc"),
                    _DrinkItem(context, "Shiraz (Syrah)"),
                    _DrinkItem(context, "Merlot"),
Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Text(
                          "Non-Alcoholic",
                          style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 20,
                            
                          ),
                        ),
                    ],
                  ),
                      
                    _DrinkItem(context, "Coca Cola"),
                    _DrinkItem(context, "Coca Cola Zero"),
                    _DrinkItem(context, "Fanta Orange"),
                    _DrinkItem(context, "Lipton Peach"),
                    _DrinkItem(context, "Lipton Sparkling"),
                    _DrinkItem(context, "Dr. Peppers"),
Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Text(
                          "Vodka",
                          style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 20,
                            
                          ),
                        ),
                    ],
                  ),
                      
                    _DrinkItem(context, "Smirnoff"),
                    _DrinkItem(context, "Bacardi Vodka"),
                    _DrinkItem(context, "Belvedere"),
                    _DrinkItem(context, "Absolut"),
                    _DrinkItem(context, "Ketel One"),
                    _DrinkItem(context, "Tito's Handmade Vodka"),
Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Text(
                          "Cocktails",
                          style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 20,
                            
                          ),
                        ),
                    ],
                  ),
                      
                    _DrinkItem(context, "Mojito"),
                    _DrinkItem(context, "Martini"),
                    _DrinkItem(context, "Old Fashioned"),
                    _DrinkItem(context, "Pina Colada"),
                    _DrinkItem(context, "Cosmopolitan"),
                    _DrinkItem(context, "Margarita"),
Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Text(
                          "Digestifs",
                          style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 20,
                            
                          ),
                        ),
                    ],
                  ),
                      
                  _DrinkItem(context, "Amaro"),
                  _DrinkItem(context, "Fernet"),
                  _DrinkItem(context, "Grappa"),
                  _DrinkItem(context, "Limoncello"),
                  _DrinkItem(context, "Cognac"),
                  _DrinkItem(context, "Sambuca"),


Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Text(
                          "Champaigne",
                          style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 20,
                            
                          ),
                        ),
                    ],
                  ),
                      
                    _DrinkItem(context, "Moët & Chandon"),
                    _DrinkItem(context, "Veuve Clicquot"),
                    _DrinkItem(context, "Dom Pérignon"),
                    _DrinkItem(context, "Laurent-Perrier"),
                    _DrinkItem(context, "Taittinger"),
                    _DrinkItem(context, "Krug"),

Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                    children: [
                      Text(
                          "Gin",
                          style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 20,
                            
                          ),
                        ),
                    ],
                  ),
                    _DrinkItem(context, "Bombay Sapphire"),
                    _DrinkItem(context, "Tanqueray"),
                    _DrinkItem(context, "Hendrick's"),
                    _DrinkItem(context, "Beefeater"),
                    _DrinkItem(context, "Gordon's"),
                    _DrinkItem(context, "Monkey 47"),
                    SizedBox(height: 160),

                  ],
                  ),
                ),
              )
              
      
              
      
      
          ]
        ),
    );
    
  }

    Widget _buildFoodTab(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.fromLTRB(0,50,0,0),
      child: Column(
            children: [
              _buildFoodPreferenceTab(context),
              SizedBox(height: 20),
              Expanded(
                child: SingleChildScrollView(
                  scrollDirection: Axis.vertical,
                  child: Column(
                    children: [
                  _MenuItem(context),
                  _MenuItem(context),
                  _MenuItem(context),
                  _MenuItem(context),
                  SizedBox(height: 160),

      
                  ],
                  ),
                ),
              )
      
              
      
      
          ]
        ),
    );

  }

    Widget _buildDrinkPreferenceTab(BuildContext context){
    return Column(
      children: [
        Padding(
          padding: const EdgeInsets.all(8.0),
          child: Card(
            color: Colors.blue.shade50, // Background color of the card
            elevation: 20,
            child: Column(
              children: [
                Padding(
                  padding: const EdgeInsets.all(8.0),
                  child: Row(
                    children: [
                      Text(
                          "Categories",
                          style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 20,
                            
                          ),
                        ),
                    ],
                  ),
                ),
                
                      Padding(
                        padding: const EdgeInsets.all(8.0),
                        child: Wrap(
                          spacing: 8.0, // Space between the chips horizontally
                          runSpacing: 4.0,
                          children: [
                            PreferenceChip("Wine"),
                            PreferenceChip("Non-Alcoholic"),
                            PreferenceChip("Vodka"),
                            PreferenceChip("Cocktails"),
                            PreferenceChip("Digestifs"),
                            PreferenceChip("Champagne"),
                            PreferenceChip("Gin"),   
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


  Widget _buildFoodPreferenceTab(BuildContext context){
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
                      "Preferences",
                      style: TextStyle(
                        fontWeight: FontWeight.bold,
                        fontSize: 20,
                      ),
                    ),
                    onExpansionChanged: (bool expanded) {
                      setState(() => isCollapsed = expanded);
                    },
                    children: [
                      Wrap(
                        spacing: 8.0, // Space between the chips horizontally
                        runSpacing: 4.0,
                        children: [
                          PreferenceChip("Gluten"),
                          PreferenceChip("Crustaceans"),
                          PreferenceChip("Eggs"),
                          PreferenceChip("Fish"),
                          PreferenceChip("Peanuts"),
                          PreferenceChip("Soy"),
                          PreferenceChip("Milk"),
                          PreferenceChip("Almond"),  
                          PreferenceChip("Hazelnut"),
                          PreferenceChip("Walnut"), 
                          PreferenceChip("Celery"),
                          PreferenceChip("Mustard"),
                          PreferenceChip("Sesame Seeds"),
                          PreferenceChip("Mollusks"),
                          PreferenceChip("Lupin"),
                          PreferenceChip("Sulfur Dioxide"),            
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


  Widget _DrinkItem(BuildContext context, String Drink){
    return Column(
      children: [
        Padding(
          padding: const EdgeInsets.fromLTRB(20, 0, 20, 10),
          child: Card(
            elevation: 20,
            child: Padding(
              padding: const EdgeInsets.all(8.0),
              child: Row(
                children: [
                  Text(Drink),
                  Spacer(),
                  IconButton(onPressed: (){}, icon: Icon(Icons.add_circle_outline_sharp))
                ],
              ),
            ),
          ),
        )

      ],
    );


  }



  Widget _MenuItem(BuildContext context){
    return Column(
      children: [
        Padding(
          padding: const EdgeInsets.fromLTRB(20, 0, 20, 10),
          child: Card(
            elevation: 20,
            child: Padding(
              padding: const EdgeInsets.all(8.0),
              child: Column(
                children: [
                  Text("5 course Menu"),
                  Divider(color: Colors.black),
                  Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Text('Risotto with seafood, saffron and lemon zest.',overflow: TextOverflow.clip, textAlign: TextAlign.center),
                  ),
                  Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Text('Tomato and watermelon gazpacho with basil oil.',overflow: TextOverflow.clip, textAlign: TextAlign.center),
                  ),
                  Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Text('Sea bass fillet with artichoke puree and fennel-tomato compote.', overflow: TextOverflow.clip, textAlign: TextAlign.center,),
                  ),
                  Padding(
                    padding: const EdgeInsets.all(8.0),
                    child: Text('Tiramisu with a twist of orange and amaretto.', overflow: TextOverflow.clip, textAlign: TextAlign.center,),
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
                                                'assets/images/food1.jpg',
                                                fit: BoxFit.cover,
                                              ),
                                            ),
                                            Text(
                                            "Rissotto with seafood, saffron and lemon zest",
                                            textAlign: TextAlign.center,
                                            style: TextStyle(
                                              fontWeight: FontWeight.bold,
                                              fontSize: 20,                                              
                                            ),
                                          ),
                                          SizedBox(height: 20),
                                          Column(
                                          crossAxisAlignment: CrossAxisAlignment.start,
                                          children: [
                                          Column(
                                            crossAxisAlignment: CrossAxisAlignment.start,
                                                children: [
                                                  Text(
                                            "Ingredients:",
                                            style: TextStyle(
                                              fontStyle: FontStyle.italic,
                                              fontSize: 15,                                              
                                            ),),
                                            Text(
                                            "• Octopus",
                                            style: TextStyle(
                                              fontSize: 15,  
                                              overflow: TextOverflow.clip                                            
                                            ),),
                                            Text(
                                            "• Chorizo ",
                                            style: TextStyle(
                                              fontSize: 15, 
                                              overflow: TextOverflow.clip                                             
                                            ),),
                                            Text(
                                            "• Onion",
                                            style: TextStyle(
                                              fontSize: 15, 
                                              overflow: TextOverflow.ellipsis                                              
                                            ),),
                                            Text(
                                            "• Olive Oil",
                                            style: TextStyle(
                                              fontSize: 15, 
                                              overflow: TextOverflow.ellipsis                                              
                                            ),),
                                            Text(
                                            "• Salt",
                                            style: TextStyle(
                                              fontSize: 15, 
                                              overflow: TextOverflow.ellipsis                                              
                                            ),),
                                            Text(
                                            "• Pepper",
                                            style: TextStyle(
                                              fontSize: 15, 
                                              overflow: TextOverflow.ellipsis                                              
                                            ),),
                                                ],
                                              ),
                                          SizedBox(height: 20,),
                                          Column(
                                            crossAxisAlignment: CrossAxisAlignment.start,
                                                children: [
                                                  Text(
                                            "Allergenes:",
                                            style: TextStyle(
                                              fontStyle: FontStyle.italic,
                                              fontSize: 15,                                              
                                            ),),
                                            Text(
                                            "• Octopus: Shellfish (if not properly cleaned)",
                                            style: TextStyle(
                                              fontSize: 15,  
                                              overflow: TextOverflow.clip                                            
                                            ),),
                                            Text(
                                            "• Chorizo: May contain pork ",
                                            style: TextStyle(
                                              fontSize: 15, 
                                              overflow: TextOverflow.clip                                             
                                            ),),
                                            Text(
                                            "• Onion: Potential allergen for some individuals",
                                            style: TextStyle(
                                              fontSize: 15, 
                                              overflow: TextOverflow.ellipsis                                              
                                            ),)
                                                ],
                                              ),
                                            SizedBox(height: 20,),
                                            Text(
                                            "Grilled octopus with chorizo oil and caramelized onion is a dish that brings together the rich flavors of the sea with the smoky essence of chorizo and the sweet notes of caramelized onion. Originating from Mediterranean and coastal regions, grilled octopus has been a culinary tradition for centuries. Its tender yet slightly chewy texture, when cooked properly, offers a delightful contrast to the crispy exterior achieved through grilling. Octopus is often praised for its ability to absorb flavors, making it a perfect canvas for complementary ingredients. Chorizo oil adds depth and complexity to the dish with its robust, spicy profile. Originating from Spain and Portugal, chorizo is a type of pork sausage seasoned with paprika and other spices, imparting a smoky, savory flavor to the oil as it is slowly rendered. When drizzled over the grilled octopus, it creates a harmonious marriage of land and sea flavors. Caramelized onion, with its sweet and savory taste, provides a subtle yet essential component to the dish. The slow cooking process caramelizes the natural sugars in the onion, resulting in a golden-brown hue and a rich, intense flavor. Its sweetness balances the heat from the chorizo oil and complements the delicate flavor of the octopus. Together, these elements create a dish that is not only visually striking but also a symphony of flavors and textures. Whether enjoyed as an appetizer or a main course, grilled octopus with chorizo oil and caramelized onion is sure to tantalize the palate and leave a lasting impression.",
                                            style: TextStyle(
                                              fontSize: 15, 
                                              overflow: TextOverflow.clip                                              
                                            ),)


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


                      }, icon: Icon(Icons.info_outline)),
                      IconButton(onPressed: (){}, icon: Icon(Icons.add_circle_outline_sharp))
                    ],
                  )


                ],
              ),
            ),
          ),
        )

      ],
    );


  }





}


class PreferenceChip extends StatefulWidget {

  String ChipString = "";

  PreferenceChip(String s){
    ChipString = s;
  }


  @override
  State<PreferenceChip> createState() => _PreferenceChip(ChipString);
}

class _PreferenceChip extends State<PreferenceChip> {
  bool selected = false;
  int Taps = 0;
  String selectedPreference = "Empty";
  String Chip = "";

  _PreferenceChip(String s){
    Chip = s;
  }


  Color determineChoice() {
    if (selectedPreference == "Empty") 
      return Colors.white;
    else if(selectedPreference == "Dislike")
      return Colors.red.shade100;
    else return Colors.blue.shade300;
  }

  @override
  Widget build(BuildContext context) {
    return ChoiceChip(
      label: Text(Chip),
      selected: selected,
      onSelected: (selectedValue) {
        setState(() {
          selected = selectedValue;
          Taps++;
          if (selected){
            selectedPreference = "Like";
          }
          else if (Taps == 2){
            selected = true;
            selectedPreference = "Dislike";
          }
          else{
            Taps = 0;
            selectedPreference = "Empty";
          }
        }
        );
      
      },
       selectedColor: determineChoice(),
    
    );

  }
}


