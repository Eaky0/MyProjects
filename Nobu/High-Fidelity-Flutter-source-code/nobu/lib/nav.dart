import 'package:flutter/material.dart';
import 'package:go_router/go_router.dart';

import 'home.dart';
import 'planner.dart';
import 'profile.dart';
import 'search.dart';

// ignore: use_key_in_widget_constructors
class NavBar extends StatefulWidget {
  const NavBar({super.key, required this.shell});

  final StatefulNavigationShell shell;

  @override
  State<NavBar> createState() => NavBarState();
}


class NavBarState extends State<NavBar>{

  int currentPageIndex = 0;

  void changePage(int index){
    currentPageIndex = index;
    widget.shell.goBranch(index, initialLocation: index == widget.shell.currentIndex);
  }
  

  @override
  Widget build(BuildContext context) {

    return Scaffold(
      bottomNavigationBar : NavigationBar(
                destinations: const [
                NavigationDestination(
                  icon: Icon(Icons.home_outlined),
                  label: "Home",
                ),
                NavigationDestination(
                  icon: Icon(Icons.search),
                  label: "Search",
                ),
                NavigationDestination(
                  icon: Icon(Icons.domain_verification_sharp),
                  label: "Planner",
                ),
                NavigationDestination(
                  icon: Icon(Icons.account_circle_outlined),
                  label: "Profile",
                )],
                backgroundColor: Colors.blue.shade100,
                indicatorColor: Colors.white,
                selectedIndex: currentPageIndex,
                onDestinationSelected: (int index){

                changePage(index);
                }
              ),
              body: widget.shell


              

    );

  }
}
