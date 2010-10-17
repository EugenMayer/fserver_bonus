<?php 
function fserver_bonus_views_plugins() {
  return array(
    'module' => 'views',
    'style' => array(
      'updatexml_projectlist' => array(
        'title' => t('Update XML Project List'),
        'help' => t('Generates a project XML feed compatible with the update module project list.'),
        'handler' => 'fserver_bonus_plugin_style_updatexml',
        'theme' => 'fserver_bonus_project_list',
        'theme path' => drupal_get_path('module', 'fserver_bonus') .'/views',
        'path' => drupal_get_path('module', 'fserver_bonus') .'/views',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'feed',
      ),
    ),
  );
}
function fserver_bonus_views_data() {
  $data = array();
}

