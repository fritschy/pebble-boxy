Pebble.addEventListener('showConfiguration', function(e) {
   var url = 'https://rawgit.com/fritschy/pebble-boxy/1.0/config/index.html'
//   var url = 'http://10.0.0.3:8000/index.html'
   console.log('Showing config page ' + url);
   Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
   var configData = JSON.parse(decodeURIComponent(e.response));
   console.log('Configuration page returned: ' + JSON.stringify(configData));

   var dict = {};
   dict['KEY_BG'] = parseInt(configData['bg'], 16);
   dict['KEY_FG'] = parseInt(configData['fg'], 16);

   // Send to watchapp
   Pebble.sendAppMessage(dict, function() {
      console.log('Send successful: ' + JSON.stringify(dict));
   }, function() {
      console.log('Send failed!');
   });
});
