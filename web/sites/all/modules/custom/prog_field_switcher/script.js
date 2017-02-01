(function($) {
	Drupal.behaviors.progfieldswitcher = {
		attach: function (context, settings) {
			function setExplicit(ampm, hour)
			{
				if(ampm == 'am')
				{
					if(hour == '00' || hour == '01' || hour == '02' || hour == '03' || hour == '04' || hour == '05' || hour == '12')
					{
						//set explicit to yes
						$('#edit-field-explicit-und').val('yes');
					}
					else
					{
						$('#edit-field-explicit-und').val('clean');
					}
				}
				else if(ampm == 'pm')
				{
					if(hour == '10' || hour == '11')
					{
						//set explicit to clean
						$('#edit-field-explicit-und').val('yes');
					}
					else
					{
						$('#edit-field-explicit-und').val('clean');
					}
				}
			}
			$('#edit-field-air-time-und-0-value-timeEntry-popup-1').change(function(){
				//var time = $('#edit-field-air-time-und-0-value-timeEntry-popup-1').value;
				var time = $(this).val();
				var ampm = time.substr(-2);
				var hour = time.substr(0,2);
				setExplicit(ampm, hour);
			});
			function pad(number)
			{
				if(number < 10)
				{
					return '0' + number;
				}
				return number;
			}
			function getCurDate()
			{
				var date = $('#edit-field-air-time-und-0-value-datepicker-popup-0').val();
				date = date.split('/');
				var time = $('#edit-field-air-time-und-0-value-timeEntry-popup-1').val();
				var ampm = time.substr(-2);
				time = time.split(':');
				time[1] = time[1].substr(0, 2);
				if(ampm == 'am' && time[0] == '12')
				{
					time[0] = '0';
				}
				if(ampm == 'pm' && time[0] != '12')
				{
					time[0] = Number(time[0]) + 12;
				}
				var dd = new Date(date[2], date[0]-1, date[1], time[0], time[1]);
				return pad((Number(dd.getMonth()) + 1)) + '/' + dd.getDate() + '/' + dd.getFullYear() + ' - ' + pad(dd.getHours()) + ':' + pad(dd.getMinutes());
			}
			function setPubDate(datetime)
			{
				$('#edit-field-published-date-und-0-value-date').val(datetime);
			}
			function getSetPubDate()
			{
				var datetime = getCurDate();
				setPubDate(datetime);
			}
			$('#edit-field-air-time-und-0-value-datepicker-popup-0').change(function(){
				getSetPubDate();
			});
			$('#edit-field-air-time-und-0-value-timeEntry-popup-1').change(function(){
				getSetPubDate();
			});
		}
	};
}(jQuery));
