import 'dart:io';

import 'package:file_selector/file_selector.dart';
import 'package:flutter/material.dart';
import 'package:window_manager/window_manager.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  await windowManager.ensureInitialized();

  WindowOptions windowOptions = const WindowOptions(
    size: Size(800, 600),
    center: true,
  );
  windowManager.setMinimumSize(const Size(200, 200));

  windowManager.waitUntilReadyToShow(windowOptions, () async {
    await windowManager.show();
    await windowManager.focus();
  });
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      home: OpenImagePage(),
    );
  }
}

class OpenImagePage extends StatefulWidget {
  const OpenImagePage({super.key});

  @override
  State<OpenImagePage> createState() => _OpenImagePageState();
}

class _OpenImagePageState extends State<OpenImagePage> {
  XFile? _file;

  Future<void> _openImageFile() async {
    const XTypeGroup typeGroup = XTypeGroup(
      label: 'images',
      extensions: <String>['jpg', 'png'],
    );
    XFile? file = await openFile(acceptedTypeGroups: <XTypeGroup>[typeGroup]);
    if (file == null) {
      return;
    }
    setState(() {
      _file = file;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Center(
        child: Column(mainAxisAlignment: MainAxisAlignment.center, children: [
          Padding(
            padding: const EdgeInsets.only(top: 8.0, bottom: 8.0),
            child: ElevatedButton(
                onPressed: () => _openImageFile(), child: const Text('Open')),
          ),
          _file != null
              ? Expanded(
                  child: Image.file(
                  File(_file!.path),
                ))
              : const SizedBox(),
        ]),
      ),
    );
  }
}
