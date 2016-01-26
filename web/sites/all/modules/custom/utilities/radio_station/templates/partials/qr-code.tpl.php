<div>
  <?php print $device['title']; ?>
</div>


<a role="button"
   data-toggle="modal"
   data-target="#modal-qr-<?php print $device['title']; ?>">

  <img src="<?php print $device['qr_image']; ?>"
       title="WWOZ <?php print $device['title']; ?> App QR code"
       alt="<?php print $device['title']; ?> QR"/>
</a>


<div>
  <a role="button"
     data-toggle="modal"
     data-target="#modal-qr-<?php print $device['title']; ?>">

    <img src="<?php print $icon_path; ?>/enlarge.gif"
         class="streams-icon"
         alt=""/>

    Enlarge QR code
  </a>
</div>
