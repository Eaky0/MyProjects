import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';
import 'package:nobu/activity.dart';
import 'package:nobu/home.dart';
import 'package:nobu/planner.dart';
import 'package:nobu/profile.dart';
import 'package:nobu/restaurantInfo.dart';
import 'package:nobu/search.dart';
import 'package:nobu/searchresults.dart';
import 'package:nobu/ReservationList.dart';
import 'nav.dart';
import 'Restaurant.dart';
import 'package:faker/faker.dart';

class AppRouting {

  static String initialRoute = "/home";

  static final navKey = GlobalKey<NavigatorState>();
  static final homeKey = GlobalKey<NavigatorState>();
  static final searchKey = GlobalKey<NavigatorState>();
  static final profileKey = GlobalKey<NavigatorState>();
  static final plannerKey = GlobalKey<NavigatorState>();


  static final GoRouter router = GoRouter(
    initialLocation: initialRoute,
    navigatorKey: navKey,
    routes:  <RouteBase> [
      

      StatefulShellRoute.indexedStack(
        builder: (context, state, shell) {return NavBar(shell : shell);},
        branches: <StatefulShellBranch> [
          StatefulShellBranch(
            navigatorKey: homeKey,
            routes: [

              GoRoute(path: "/home",
                      name: "Home",
                      builder: (context, state) { return home(key: state.pageKey);},
                      
                      routes: [

                        GoRoute(
                          
                          path: "restaurantinfo",
                          name: "RestaurantInfo",
                          builder: (context, state) { return restaurantInfo(restaurantName: faker.food.restaurant(), cuisine: faker.food.cuisine(), rating : faker.randomGenerator.integer(50) / 10, key: state.pageKey);}
                          
                        ),
                        GoRoute(
                        path: "reservationslist",
                        name: "ReservationsList",
                        builder: (context, state) { return ReservationListPage(key: state.pageKey);},
                        routes : [
                        GoRoute(
                          path: "activity",
                          name: "Activity",
                          builder: (context, state) {
                            final restaurant = ModalRoute.of(context)!.settings.arguments as Restaurant;
                            return ActivityPage(key: state.pageKey, restaurant: restaurant);
                          },
                        ),


                        ]
                        )



                      ]
                      
                      
                      )
              
              

            ]

  
          
          ),

          StatefulShellBranch(
            navigatorKey: searchKey,
            routes: [
              
              GoRoute(path: "/search",
                      name: "Search",
                      builder: (context, state) { return SearchPage(key: state.pageKey);},
                      
                      
                      
                      routes: [

                        GoRoute(
                          
                          path: "searchresults",
                          name: "SearchResults",
                          builder: (context, state) { return SearchResultsPage(key: state.pageKey);}
                          
                        )



                      ]
                      
                      
                      
                      
                      
                      
                      )
            ]
  
          
          ),

          StatefulShellBranch(
            navigatorKey: plannerKey,
            routes: [
              
              GoRoute(path: "/planner",
                      name: "Planner",
                      builder: (context, state) { return PlannerPage(key: state.pageKey);})
            ]
  
          
          ),

          StatefulShellBranch(
            navigatorKey: profileKey,
            routes: [
              
              GoRoute(path: "/profile",
                      name: "Profile",
                      builder: (context, state) { return ProfilePage(key: state.pageKey);})
              
            ]
  
          
          )

          


          
          
        ]
        
        
        ),
    

    ]

  );

}
