function gui = VisionLayout( gui, fig )
%VisionCurrentLayout Load a simple GUI window showing car vision and motor
%load current.
    
    % open a new figure
    fig = gui.newFigure;
    
    % initialise views
    % TODO - Add titles
    gui = gui.addView(@LinescanView, 'linescan0', 'figure', fig, 'position', [1,2,1]);
    gui = gui.addView(@LinescanView, 'linescan1', 'figure', fig, 'position', [1,2,2]);
end

