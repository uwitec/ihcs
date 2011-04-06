var pageMap = new Object();
pageMap['light'] = "lighting.html?curr=light";
pageMap['stereo'] = "stereo.html?curr=stereo";
pageMap['projector'] = "projector.html?curr=projector";
pageMap['proScreen'] = "proscreen.html?curr=proScreen";
pageMap['models'] = "models.html?curr=models";
pageMap['veneBlind'] = "veneblind.html?curr=veneBlind";
pageMap['curtain'] = "curtain.html?curr=curtain";
pageMap['awning'] = "awning.html?curr=awning";
pageMap['rolBlind'] = "rollerblind.html?curr=rolBlind";


function callBack(obj, imgNum, imgName, method){
	
	if(obj.src.indexOf("_click") < 0){
		method();
	}

	changePic(obj, imgNum, imgName);
}

function changePic(obj, imgNum, imgName){
	var divObj = document.getElementById('mainDiv');
	var imgArr = divObj.getElementsByTagName("img");
	for(var i = 0; i < imgArr.length; i++){
		var srcPath = imgArr[i].src;
		if(srcPath.indexOf("_click") > -1){
			imgArr[i].src = srcPath.substring(0,(srcPath.length - 10) ) + ".gif";
		}
	}
	var temp = obj.src;
	if(temp.indexOf("_click") < 0){
		//obj.src = 'images/' + imgName + '_' + imgNum + ".gif";
	//}else{
		obj.src = 'images/' + imgName + '_' + imgNum + "_click.gif";
	}
}

function cgiCallback(type,url,data,successMethod){
	$.ajax({
		type:type,
		datatype:'html',
		cache:false,
		async: false,
		url:url,
		data:data,
		timeout: 2000, 
		success:
			successMethod,
		});
}


//将第一个表单提交
function submit(){
	//document.form[0].method="post";
	document.forms[0].submit();
}

function submit(formId){
	document.forms[formId].submit();
}

//url转向
function hrefURL(url){
	document.location.href = url;
}

function getUrlParms(key){
	var query = location.search.substring(1);//获取查询串
	var pairs = query.split("&");//在逗号处断开
    for(var i=0; i<pairs.length; i++)
    {
		//var pos = pairs[i].indexOf('=');//找name=value
		//if(pos == -1)   continue;//如果没有找到就跳过
		if(pairs[i].indexOf( key + '=' ) > -1 ){
			return pairs[i].substring(key.length + 1);
		}
    }
    return "";
}

function getBfKey(currPage){
	var bfKey = "rolBlind";
	for( var key in pageMap ){
		if(key == currPage){
			return bfKey;
		}
		bfKey = key;
	}
	return bfKey;
}

function getNtKey(currPage){
	var ntKey = "";
	for( var key in pageMap ){
		if(ntKey == currPage){
			return key;
		}
		if(key == currPage){
			ntKey = currPage;
		}
	}
	return "light";
}

//上一页
function beforePage(){
	var currPage = "light";
	currPage = getUrlParms("curr");
	currPage = getBfKey(currPage);
	hrefURL( pageMap[currPage] );
}
//下一页
function nextPage(){
	var currPage = "light";
	currPage = getUrlParms("curr");
	currPage = getNtKey(currPage);
	hrefURL( pageMap[currPage] );
}
