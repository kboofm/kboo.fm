<div class="modal fade"
     id="modal-qr-<?php print $device['title']; ?>"
     tabindex="-1"
     role="dialog"
     aria-labelledby="modal-qr-<?php print $device['title']; ?>-label">

  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button"
                class="close"
                data-dismiss="modal"
                aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>

        <h4 class="modal-title"
            id="modal-qr-<?php print $device['title']; ?>-label">
          <?php print $device['title']; ?> QR Code
        </h4>
      </div>


      <div class="modal-body text-center">
        <img src="<?php print $device['qr_image']; ?>"
             title="WWOZ <?php print $device['title']; ?> App QR code"
             alt="<?php print $device['title']; ?> QR"/>
      </div>
    </div>
  </div>
</div>

