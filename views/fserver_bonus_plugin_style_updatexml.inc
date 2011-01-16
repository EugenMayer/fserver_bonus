<?php
class fserver_bonus_plugin_style_updatexml extends views_plugin_style {
  /**
   * List of project XML elements.
   */
  protected function project_elements() {
    return array('title', 'short_name', 'dw:creator', 'link', 'project_status', 'sourcecode_type', 'sourcecode_uri');
  }
  

 	/**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();

    $project_defaults = array();
    foreach ($this->project_elements() as $element) {
      $project_defaults[$element] = '';
    }
    $options['project'] = array('default' => $project_defaults);
    $options['terms'] = array('default' => array());
    $options['nid'] = array( 'default' => false);  
    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    // Build list of valid fields
    $options = array();
    $handlers = $this->display->handler->get_handlers('field');
    foreach ($handlers as $field => $handler) {
      if (empty($handler->options['exclude'])) {
        $options[$field] = $handler->label();
      }
    }
    $form['nid'] = array(
      '#title' => t('Nid'),
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $this->options['nid'],
    );

    $form['project'] = array(
      '#tree' => TRUE,
      '#type' => 'fieldset',
      '#title' => t('Project fields'),
    );
    foreach ($this->project_elements() as $element) {
      $form['project'][$element] = array(
        '#title' => $element,
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => $this->options['project'][$element],
      );
    }
   
    $form['terms'] = array(
      '#title' => t('Terms'),
      '#type' => 'checkboxes',
      '#options' => $options,
      '#default_value' => $this->options['terms'],
    );
  }
  
  function preprocess(&$vars) {
    $fields = $vars['view']->field;

    // Build project XML values
    $projects = array();
    foreach ($vars['view']->style_plugin->rendered_fields as $record) {
      $project = array(
        'apis' => array(),
        'terms' => array(),
      );
      // Get the current project node id. The field is defined in the options before
      $nid = $record[$vars['options']['nid']];
     
      // Get all the APIs by fetching all the existing releases using the already existing view      
      $result = views_get_view_result('fserver_releases','page_1', $nid);
      foreach($result as $releases) {
        $api = $releases->node_data_field_fserver_project_field_fserver_api_value;
        // We use the $api as key to avoid dublicates :)
        $project['apis'][$api] = $api;
      }
      
      // fetch all the general project data  
      foreach ($vars['options']['project'] as $element => $field) {
        $project[$element] = $record[$field];
      }
      
      // finally handle terms which are a bit special. The label will be the name later
      // value will be the value.
      foreach ($vars['options']['terms'] as $element => $field) {
        if($field === 0) {
          continue;
        }
        $project['terms'][$fields[$field]->options['label']] = $record[$field];    
      }
      
      // published is a bolean state, lets convert it to what the update feed needs
      if($project['project_status'] == 'True') {
        $project['project_status'] = 'published';
      } 
      else {
        $project['project_status'] = 'unpublished';
      }
      
      // finally add the project
      $projects[] = $project; 
    }
    // Finalize
    $vars['projects'] = $projects;
    drupal_set_header('Content-Type: application/xml; charset=utf-8');
  }
}
