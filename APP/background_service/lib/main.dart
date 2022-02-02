import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

import 'dart:typed_data';
import './models/device.dart';

import 'device_tile.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demo',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      debugShowCheckedModeBanner: false,
      home: MyHomePage(),
    );
  }
}

class MyHomePage extends StatefulWidget {
  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  void startServiceInPlatform(String s) async {
    if (Platform.isAndroid) {
      var methodChannel = MethodChannel("com.retroportalstudio.messages");
      String data = await methodChannel.invokeMethod(s);
      debugPrint(data);
    }
  }

  bool called = false;
  void server() async {
    if (called) {
      return;
    }
    startServiceInPlatform("انتظار");

    called = true;
    // bind the socket server to an address and port
    //Wakelock.enable();
    //Screen.keepOn(true);
    final server = await ServerSocket.bind(InternetAddress.anyIPv4, 4567);

    // listen for clent connections to the server
    server.listen((client) {
      handleConnection(client);
    });
  }

  void handleConnection(Socket client) {
    print('Connection from'
        ' ${client.remoteAddress.address}:${client.remotePort}');

    // listen for events from the client
    client.listen(
      // handle data from the client
      (Uint8List data) async {
        await Future.delayed(Duration(seconds: 1));
        final message = String.fromCharCodes(data);
        setState(() {
          Device d = new Device(
              ip: client.remoteAddress.address,
              num: message,
              time: DateTime.now());
          devices.add(d);

          startServiceInPlatform(message);
        });
        client.close();
      },

      // handle errors
      onError: (error) {
        print(error);
        client.close();
      },

      // handle the client closing the connection
      onDone: () {
        print('Client left');
        client.close();
      },
    );
  }

  List devices = [
    new Device(
        ip: 'client.remoteAddress.address', num: '1', time: DateTime.now())
  ];
  @override
  Widget build(BuildContext context) {
    server();
    var reversedList = new List.from(devices.reversed);

    return Scaffold(
      appBar:
          AppBar(title: Text("اشعارات"), centerTitle: true, actions: <Widget>[
        FlatButton.icon(
          icon: Icon(
            Icons.delete,
            color: Colors.red,
          ),
          label: Text('محي الكل'),
          onPressed: () {
            setState(() {
              devices.clear();
            });
          },
        ),
      ]),
      body: ListView.builder(
        itemCount: devices.length,
        itemBuilder: (context, index) {
          return DeviceTile(device: reversedList[index]);
        },
      ),
    );
  }
}
