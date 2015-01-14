function gui = VisionCurrentLayout( gui, fig )
%VisionCurrentLayout Load a simple GUI window showing car vision and motor
%load current.
    
    gui = gui.addViews(...
        LinescanView(gui.session, 'linescan0', 'figure', fig, 'position', [2,2,1]),...
        TrackPositionView(gui.session, 'TrackPosition', 'figure', fig, 'position', [2,2,3]),...
        MotorCurrentView(gui.session, 'i_rl', 'figure', fig, 'position', [2,2,2]),...
        MotorCurrentView(gui.session, 'i_rr', 'figure', fig, 'position', [2,2,4])...
    );
end

