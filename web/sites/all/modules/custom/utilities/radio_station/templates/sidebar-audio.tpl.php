<h2 class="bg-primary">
  Latest Audio
</h2>


<?php foreach ($episodes as $episode): ?>
  <p>
    <span class="truncate">
      <?php print $episode['program']; ?>
    </span>
    <br />

    <a href="<?php print $episode['url']; ?>"
       class="truncate">
      <?php print $episode['title']; ?>
    </a>
  </p>
<?php endforeach; ?>


<p>
  <a class="more-link bg-primary"
     href="/audio">
    More
  </a>
</p>

