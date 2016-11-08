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
			$('#edit-field-air-time-und-0-value-timeEntry-popup-1').change();
		}
	};
}(jQuery));
