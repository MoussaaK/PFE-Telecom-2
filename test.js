[{
    "id": "d8144e94.d37ef8",
    "type": "inject",
    "z": "6bda22e9.61f89c",
    "name": "",
    "topic": "",
    "payload": "",
    "payloadType": "date",
    "repeat": "",
    "crontab": "",
    "once": false,
    "onceDelay": 0.1,
    "x": 92,
    "y": 70,
    "wires": [
        ["c7cc437c.75c4e"]
    ]
}, {
    "id": "c7cc437c.75c4e",
    "type": "http request",
    "z": "6bda22e9.61f89c",
    "name": "get_HTML",
    "method": "GET",
    "ret": "txt",
    "url": "http://[fd00::212:4b00:60d:60d0]",
    "tls": "",
    "x": 303.5,
    "y": 24,
    "wires": [
        ["a14717e1.687308", "8c100464.f64dd"]
    ]
}, {
    "id": "8c100464.f64dd",
    "type": "debug",
    "z": "6bda22e9.61f89c",
    "name": "",
    "active": true,
    "tosidebar": true,
    "console": false,
    "tostatus": false,
    "complete": "payload",
    "x": 535.5,
    "y": 25,
    "wires": []
}, {
    "id": "a14717e1.687308",
    "type": "function",
    "z": "6bda22e9.61f89c",
    "name": "extract_IPv6",
    "func": "var strings = msg;\nvar IPv6s = [];\nstrings = strings.substring(\n                  strings.lastIndexOf(\"<ul>\"),\n                  strings.lastIndexOf(\"</ul>\")\n                  ).split(\"<li>\");\nfor (var line of strings) {\n  if (!line.startsWith(\"<ul>\")) {\n    IPv6s.push(\n          line.substring(0, line.indexOf(\" (\"))\n        );\n  }\n}\n\nreturn IPv6s;\n",
    "outputs": 1,
    "noerr": 0,
    "x": 503.5,
    "y": 82,
    "wires": [
        ["d95c3865.493a2"]
    ]
}, {
    "id": "d95c3865.493a2",
    "type": "debug",
    "z": "6bda22e9.61f89c",
    "name": "",
    "active": true,
    "tosidebar": true,
    "console": false,
    "tostatus": false,
    "complete": "true",
    "x": 704.5,
    "y": 82,
    "wires": []
}]
