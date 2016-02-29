<h2 class="bg-info">
  Recent Playlists
</h2>


<?php foreach ($playlists as $playlist): ?>
  <p>
    <span class="truncate">
      <?php print $playlist['program']; ?>
    </span>
    <br />

    <a href="<?php print $playlist['url']; ?>"
       class="truncate">
      <?php print $playlist['title']; ?>
    </a>
  </p>
<?php endforeach; ?>


<p>
  <a class="more-link bg-info"
     href="#">
    More
  </a>
</p>
