<project>
  <title><?php echo $details['title'];?></title>
  <short_name><?php echo $details['short_name'];?></short_name>
  <link><?php echo $details['link'];?></link>
  <dc:creator xmlns:dc="http://purl.org/dc/elements/1.1/"><?php echo $details['dw:creator']?></dc:creator>
  <terms>
    <?php
    foreach($details['terms'] as $name => $value) {
      echo "<term><name>$name</name><value>$value</value></term>";
    }
    ?>
  </terms>  
  <project_status><?php echo $details['project_status']; ?></project_status>
  <api_versions>
    <?php
    foreach($details['apis'] as $api) {
      echo "<api_version>$api</api_version>";
    }
    ?>
  </api_versions>
  <sourcecode>
    <type><?php print $details['sourcecode_type']; ?></type>
    <uri><?php print $details['sourcecode_uri']; ?></uri>
  </sourcecode>
 </project>