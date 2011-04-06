function daylightMethod(){

	cgiCallback('GET',
		'/smartHome',
		'action=203&groupAddr=128&cmd=10',
		function(msg){
			//if($.trim(msg) == "1"){	
				//$("#btnOn").attr("disabled","disabled");
				//$("#btnOff").removeAttr("disabled");
			//}
		}
	);
}

function confMethod(){

	cgiCallback('GET',
		'/smartHome',
		'action=203&groupAddr=128&cmd=11',
		function(msg){
		}
	);
}

function partyMethod(){

	cgiCallback('GET',
		'/smartHome',
		'action=203&groupAddr=128&cmd=12',
		function(msg){
		}
	);
}

function breakMethod(){

	cgiCallback('GET',
		'/smartHome',
		'action=203&groupAddr=128&cmd=13',
		function(msg){
		}
	);
}

function cinemaMethod(){

	cgiCallback('GET',
		'/smartHome',
		'action=203&groupAddr=128&cmd=14',
		function(msg){
		}
	);
}

function teaMethod(){

	cgiCallback('GET',
		'/smartHome',
		'action=203&groupAddr=128&cmd=15',
		function(msg){
		}
	);
}

function sliderChange(value, minValue, maxValue, valueChangeMethod){
	$( "#slider-vertical" ).slider({
		animate: true,
		orientation: "vertical",
		range: "min",
		min: minValue,
		max: maxValue,
		value: value,
		change: function(event,ui){
			valueChangeMethod(ui.value);
		}
	});
	//$( "#slider-vertical" ).bind('slide', valueChangeMethod($( "#slider-vertical" ).slider( "value" )));
	//$( "#amount" ).val( $( "#slider-vertical" ).slider( "value" ) );
}

//$('body').everyTime('1s','A',addValue);
//setInterval(addValue,100);
//while(flag){
	//setTimeout("addValue()",100);
	//sleep(100);
//}
function sliderUp(obj, imgNum, imgName, valueChangeMethod){
	changePic(obj, imgNum, imgName);
	//addValue();
	sliderChange(maxValue, minValue, maxValue, valueChangeMethod);
}

function sliderStop(obj, imgUrl){
	obj.src = imgUrl;
}

function sliderStatus(obj, imgNum, imgName, valueChangeMethod, stopMethod){
	changePic(obj, imgNum, imgName);
	stopMethod();
	//sliderChange(currValue, minValue, maxValue, valueChangeMethod);
}

function sliderDn(obj, imgNum, imgName, valueChangeMethod){
	changePic(obj, imgNum, imgName);
	//mulValue();
	sliderChange(minValue, minValue, maxValue, valueChangeMethod);
}

function sleep(numberMillis) { 
   var now = new Date();
   var exitTime = now.getTime() + numberMillis;  
   while (true) { 
       now = new Date(); 
       if (now.getTime() > exitTime)    return;
    }
}

function addValue(){
	currValue = currValue + 1;
	sliderChange(currValue);
}

function mulValue(){
	currValue = currValue - 1;
	sliderChange(currValue);
}

function lightChange(value){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=1&cmd=' + value,
		function(msg){
			if($.trim(msg) == "1"){
			}
		}
	);
}

function lightStop(){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=1&cmd=3',
		function(msg){
		}
	);
}

function stereoChange(value){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=2&cmd=' + value,
		function(msg){
			if($.trim(msg) == "1"){
			}
		}
	);
}

function stereoStop(){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=2&cmd=3',
		function(msg){
		}
	);
}

function projectorChange(value){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=3&cmd=' + value,
		function(msg){
			if($.trim(msg) == "1"){
			}
		}
	);
}

function projectorStop(){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=3&cmd=3',
		function(msg){
		}
	);
}

function screenChange(value){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=4&cmd=' + value,
		function(msg){
			if($.trim(msg) == "1"){
			}
		}
	);
}

function screenStop(){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=4&cmd=3',
		function(msg){
		}
	);
}

function venetianChange(value){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=5&cmd=' + value,
		function(msg){
			if($.trim(msg) == "1"){
			}
		}
	);
}

function venetianStop(){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=5&cmd=3',
		function(msg){
		}
	);
}

function curtainChange(value){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=6&cmd=' + value,
		function(msg){
			if($.trim(msg) == "1"){
			}
		}
	);
}

function curtainStop(){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=6&cmd=3',
		function(msg){
		}
	);
}

function awningChange(value){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=7&cmd=' + value,
		function(msg){
			if($.trim(msg) == "1"){
			}
		}
	);
}

function awningStop(){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=7&cmd=3',
		function(msg){
		}
	);
}

function rollerChange(value){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=8&cmd=' + value,
		function(msg){
			if($.trim(msg) == "1"){
			}
		}
	);
}

function rollerStop(){
	cgiCallback('GET',
		'/smartHome',
		'action=202&shortAddr=8&cmd=3',
		function(msg){
		}
	);
}