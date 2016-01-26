<div id="streams-page">
  <a class="launch-player cursor-pointer"
     data-stream="one">

    <img class="img-responsive margin-horizontal-auto"
         src="<?php print $icon_path; ?>/player-ad-gray.png"/>
  </a>


  <h2>
    Other ways to listen WWOZ 90.7 FM
  </h2>


  <h5>
    On your phone, tablet or mobile device
  </h5>


  <hr/>


  <ul class="list-unstyled">
    <?php foreach ($devices as $device): ?>
      <li>
        <?php
        include 'partials/device-item.tpl.php';
        ?>
      </li>
    <?php endforeach; ?>
  </ul>


  <div id="qr-codes-accordion">
    <div class="panel panel-default">

      <div class="panel-heading">
        <div class="cursor-pointer"
             data-toggle="collapse"
             data-target="#qr-codes-body"
             data-parent="#qr-codes-accordion">

          <img src="<?php print $icon_path; ?>/QR-gray.png" 
               class="streams-icon"/>

          Get QR codes

          <img src="<?php print $icon_path; ?>/unfurl-arrow-gray.png" 
               class="unfurl-icon"/>
        </div>
      </div>


      <div id="qr-codes-body"
           class="panel-body collapse">

        <div class="row">
          <?php foreach ($devices as $device): ?>
            <div class="col-sm-4">
              <?php
              include 'partials/qr-code.tpl.php';
              ?>
            </div>
          <?php endforeach; ?>
        </div>

      </div>
    </div>
  </div>


  <?php
  foreach ($devices as $device):
    include 'partials/qr-modal.tpl.php';
  endforeach;
  ?>

  <div id="other-devices-accordion">
    <div class="panel panel-default">
  
      <div class="panel-heading">
        <div class="cursor-pointer"
             data-toggle="collapse"
             data-target="#other-devices-body"
             data-parent="#other-devices-accordion">

          <img src="<?php print $icon_path; ?>/mobile-gray.png"
               class="streams-icon"/>

          On other mobile devices

          <img src="<?php print $icon_path; ?>/unfurl-arrow-gray.png" 
               class="unfurl-icon"/>
        </div>
      </div>


      <div id="other-devices-body"
           class="panel-body collapse">

        <h5>
          Listen on Other Mobile Devices
        </h5>


        <ul>
          <li>
            <a href="http://www.yourmuze.fm/"
               target="_blank">
              Yourmuze.FM
            </a>
            , free service that lets you stream when you visit their website
          </li>
        </ul>

      </div>
    </div>
  </div>


  <div class="well second-stream">
    <div class="row">

      <div class="col-sm-2">
        <img src="<?php print $icon_path; ?>/second-stream-thumb.jpg" />
      </div>


      <div class="col-sm-10">
        <p>
          Listen to more New Orleans music on WWOZ-2!
        </p>


        <a class="launch-player cursor-pointer"
           data-stream="two">

          Listen Now
        </a>
      </div>

    </div>
  </div>


  <h5>
    On your computer
  </h5>

  <hr />

  <ul class="list-unstyled">
    <li>
      <a href=""
         title="Listen to Flash stream at 128k stereo in new browser window">

        <img src="<?php print $icon_path; ?>/Flash-gray.png"
             class="streams-icon"/>

        <span>
          Flash player 128k stereo
        </span>
      </a>

      (formerly our default player)
    </li>

    <li>
      <a href="/listen/hi">
  
        <img src="<?php print $icon_path; ?>/MP3-gray.png"
             class="streams-icon"/>

        <span>
          MP3 128k stereo
        </span>
      </a>
    </li>

    <li>
      <a href="/listen/lo">

        <img src="<?php print $icon_path; ?>/MP3-gray.png"
           class="streams-icon"/>

        <span>
          MP3 24k stereo
        </span>
      </a>
    </li>

    <li>
      <a href="/listen/windowsmedia">

          <img src="<?php print $icon_path; ?>/WM-gray.png"
               class="streams-icon"/>

          <span>
            Windows Media 64k stereo
          </span>
        </a>
    </li>
  </ul>  

  <div class="stream-help">
    <h4>
      Stream Help
    </h4>

    <p>  
      Having problems while listening using your web browser? Please try
      <a href="http://www.refreshyourcache.com/"
         target="_blank">
         clearing your browser's cache.
      </a>
    </p>

    <ul class="list-unstyled">
      <li>
        <a href="/about/connection-troubleshooting-faq">
          <img src="<?php print $icon_path; ?>/faq-gray.png" 
               class="streams-icon"/>

          Troubleshooting FAQ
        </a>
      </li>

      <li>
        <a href="/contact/stream">
          <img src="<?php print $icon_path; ?>/report-gray.png"
               class="streams-icon"/>

          Report a problem
        </a>
      </li>
    </ul>  
  </div>  
</div>  