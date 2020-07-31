var http = require('http');
var fs = require('fs');
var url = require('url');
// http, fs, url -> node js의 모듈

var app = http.createServer(function(request,response){
  var _url = request.url;
  var queryData = url.parse(_url, true).query;
  var pathname = url.parse(_url, true).pathname;
  var title = queryData.id;

  console.log(queryData.id);
  if(_url == '/'){
      title = 'Welcome';
  }
  if(_url == '/favicon.ico'){
    return response.writeHead(404);
  }

  if(pathname == '/')
  {
    if(queryData.id == undefined)
    {
      fs.readdir(`./data`, function(err, filelist){
        var descriptions = "Hello World";
        var list = `<ul>`;

        var i = 0;
        while(i<filelist.length)
        {
          list = list + `<li><a href="/?id=${filelist[i]}">${filelist[i]}</a></li>`;
          i = i+1;
        }

        list = list + `</ul>`;

        var template = `
        <!doctype html>
        <html>
        <head>
          <title>WEB1 - ${title}</title>
          <meta charset="utf-8"
        </head>
        <body>
          <h1><a href="/">WEB</a></h1>
          <ol>
            ${list}
          </ol>
          <h2>${title}</h2>
          <p>${descriptions}</p>
        </body>
        </html>
        `
        response.writeHead(200);
        response.end(template);
      });
    }
    else
    {
      fs.readdir(`./data`, function(err, filelist){
        var list = `<ul>`;
        var i = 0;
        while(i<filelist.length)
        {
          list = list + `<li><a href="/?id=${filelist[i]}">${filelist[i]}</a></li>`
          i = i+1;
        }

        list = list + '<ul>';
        fs.readFile(`data/${title}`, 'utf8', function(err, descriptions){
          var template = `
          <!doctype html>
          <html>
          <head>
            <title>WEB1 - ${title}</title>
            <meta charset="utf-8"
          </head>
          <body>
            <h1><a href="/">WEB</a></h1>
            <ol>
              ${list}
            </ol>
            <h2>${title}</h2>
            <p>${descriptions}</p>
          </body>
          </html>
          `
          response.writeHead(200);
          response.end(template);
        });
      });
    }
  }
  else
  {
    response.writeHead(404);
    response.end("Not Found");
  }
 
});
app.listen(3000);