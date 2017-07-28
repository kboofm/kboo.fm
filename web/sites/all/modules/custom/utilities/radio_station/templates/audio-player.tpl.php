<?php foreach ($audio_files as $index => $audio_file): ?>
  <script type="text/javascript">
   jQuery(document).ready(function () {
     new App.Player.Audio("#station-audio-wrapper-<?php print $audio_file['fid']; ?>");
    });
  </script>


  <div id="station-audio-wrapper-<?php print $audio_file['fid']; ?>" class="station-audio-player">
    <div class="jp-jplayer"
         data-endpoint="<?php print $audio_file['filepath']; ?>">
    </div>


    <div id="station-audio-container-<?php print $audio_file['fid']; ?>"
         class="jp-audio">

      <div class="jp-type-single">
        <div class="jp-gui jp-interface">
          <ul class="jp-controls">
            <li>
              <a href="javascript:;" class="jp-play" tabindex="1">play</a>
            </li>

            <li>
              <a href="javascript:;" class="jp-pause" tabindex="1">pause</a>
            </li>

            <li>
              <a href="javascript:;" class="jp-mute" tabindex="1" title="mute">mute</a>
            </li>

            <li>
              <a href="javascript:;" class="jp-unmute" tabindex="1" title="unmute">unmute</a>
            </li>
          </ul>


          <div class="jp-progress">
            <div class="jp-seek-bar">
              <div class="jp-play-bar"></div>
            </div>
          </div>


          <div class="jp-duration"></div>
        </div>


        <div class="jp-title">
          <ul>
            <li>KBOO</li>
          </ul>
        </div>


        <div class="jp-no-solution">
          <span>Update Required</span>

          To play the media you will need to either update your browser to a recent version or update your

          <a href="http://get.adobe.com/flashplayer/"
             target="_blank">Flash plugin</a>.
        </div>
      </div>
    </div>
  </div>

  <?php if ($allow_download): ?>
    <a href="<?php print $audio_file['filepath']; ?>">
      Download audio file
    </a>
  <?php endif; ?>
<?php endforeach; ?>

