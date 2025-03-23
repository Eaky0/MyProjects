import 'package:flutter/material.dart';
import 'package:nobu/router.dart';
import 'FavoritesState.dart';
import 'package:provider/provider.dart';

import 'nav.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return ChangeNotifierProvider(
      create: (context) => FavoritesState(),
      child: MaterialApp.router(
        title: 'Nobu',
        theme: ThemeData(
          colorScheme: ColorScheme.fromSeed(seedColor: Colors.white),
          useMaterial3: true,
        ),
      routerConfig: AppRouting.router,
      ),









      
    );
  }
}



