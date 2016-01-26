<div class="row">
  <div class="col-sm-12 show-hosts">


    <p class="margin-vertical-lg">
      For the sheer love of the music, WWOZ show hosts (DJs) welcome you to share the sounds of their personal collections. All are volunteers donating several hours weekly on the mic, not to mention the many more hours collecting and programming the recordings.
      Our show hosts are part and parcel of the music community of New Orleans. Some are musicians, others are loyal live-music devotees. You get the local's perspective on every show.
      The station does not provide these aficionados with playlists; each show is unique and hand-picked just for you. What's more, they are not influenced by commercial considerations (i.e., record labels, music venues, etc. do not pay for play). Pure intent, pure music, pure groove.
    </p>


    <?php include 'partials/programs-show-hosts-form.tpl.php'; ?>


    <?php include 'partials/pager-alphabetic.tpl.php'; ?>


    <?php foreach ($profiles as $key => $data): ?>
      <h4 id="<?php print $key; ?>">
        <?php print $key; ?>
      </h4>


      <ul class="show-host-list">
        <?php foreach ($data as $profile): ?>
          <li>
            <a href="<?php print $profile['url']; ?>">
              <?php print $profile['title']; ?>
            </a>
          </li>
        <?php endforeach; ?>
      </ul>
    <?php endforeach; ?>


    <?php include 'partials/pager-alphabetic.tpl.php'; ?>


  </div>
</div>


